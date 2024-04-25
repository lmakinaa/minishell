/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/25 22:08:47 by ijaija           ###   ########.fr       */
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
	return (0);
}

/*
* it focuses on redirections
*/
int	tokenize_part2(t_token **cmd)
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
	}
	return (0);
}

int	tokenize_part3(t_token **cmd)
{
	int	i;
	int	found;

	i = -1;
	found = 0;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN && !found)
		{
			cmd[i]->type = T_CMD;
			found = 1;
		}
		else if (found && cmd[i]->type == T_UNKNOWN)
			cmd[i]->type = T_ARG;
	}
	return (0);
}

void print_command_elements(t_command *command)
{
	char	buff[50];
	int     bytes_read;

	printf("Command: %s\n", command->cmd);
	printf("Arguments:\n");
	for (int i = 0; command->args[i] != NULL; i++)
		printf("%s\n", command->args[i]);
	printf("Output Files:\n");
	if (command->output_files != NULL)
		for (int i = 0; command->output_files[i] != NULL; i++)
			printf("%s\n", command->output_files[i]);
	printf("Output Redirection Type: %d\n", command->output_redir_type);
	printf("Input File: %s\n", command->input_file);
	if (command->std_input == -1)
		return ;
	printf("Standard Input:\n%d\n", command->std_input);
	buff[0] = '\0';
	while ((bytes_read = read(command->std_input, buff, 49)) > 0)
    {
        buff[bytes_read] = '\0';
        printf("%s", buff);
    }
	//close(command->std_input);
}

int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root)
{
	t_command	*command;

	if (!root)
		return (0);
	if (execute_tree(session, env, root->left) == -1)
		return (-1);
	if (execute_tree(session, env, root->right) == -1)
		return (-1);
	if (root->command)
	{
		if (tokenize_part2(root->command) == -1)
			return (-1);
		root->command = expander(session, env, root->command);
		if (!root->command)
			return (-1);
		if (tokenize_part3(root->command) == -1)
			return (-1);
		command = parse_cmd(session, env, root->command);
		print_command_elements(command);
	}
	return (0);
}
