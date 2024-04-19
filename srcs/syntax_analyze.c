/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyze.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 23:18:37 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/*
* tok have the EOL word and returns -1 if fails
*/
int	heredoc_handle(t_memsession *session, t_token *tok)
{
	char	*file;
	char	*line;
	char	*eol;
	int		fd;

	fd = 0;
	eol = custom_strjoin(session, tok->value, "\n");
	file = NULL;
	write(1, "# ", 2);
	line = get_next_line(session, fd);
	while (line)
	{
		if (!ft_strcmp(line, eol))
			break ;
		file = custom_strjoin(session, file, line);
		del_from_session(session, line);
		write(1, "# ", 2);
		line = get_next_line(session, fd);
	}
	tok->value = file;
	tok->type = T_STD_INPUT;
	//printf("file->%s", file);
	return (0);
}

/*
* it focuses on redirections
*/
int	tokenize_redirectors(t_memsession *session, t_token **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_OUT_REDIR || cmd[i]->type == T_APPEND_REDIR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (syntax_error("near > or >>", 12), -1);
			cmd[i + 1]->type = T_OUTPUT_FILE;
		}
		else if (cmd[i]->type == T_INPUT_REDIRECTOR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (syntax_error("near <", 6), -1);
			cmd[i + 1]->type = T_INPUT_FILE;
		}
		else if (cmd[i]->type == T_HERDOC)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (syntax_error("near <<", 7), -1);
			heredoc_handle(session, cmd[i + 1]);
		}
	}
	return (0);
}

int	more_parse(t_memsession *session, t_tnode *root)
{
	if (!root)
		return (0);

	if (more_parse(session, root->left) == -1)
		return (-1);
	if (more_parse(session, root->right) == -1)
		return (-1);
	if (root->command)
	{
		if (tokenize_redirectors(session, root->command) == -1)
			return (-1);
		
	}
	return (0);
}
