/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyze.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 16:57:43 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/*
* tok have the EOL word and returns -1 if fails
*/
int	heredoc_handle(t_token *tok);

/*
* it focuses on redirections
*/
int	tokenization_part2(t_token **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_OUT_REDIR || cmd[i]->type == T_APPEND_REDIR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (syntax_error("near >", 6), -1);
			cmd[i + 1]->type = T_OUTPUT_FILE;
		}
		else if (cmd[i]->type == T_INPUT_REDIRECTOR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (syntax_error("near <", 6), -1);
			cmd[i + 1]->type = T_OUTPUT_FILE;
		}
		else if (cmd[i]->type == T_HERDOC)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (syntax_error("near <", 6), -1);
			//return (heredoc_handle(cmd[i + 1]));
		}
	}
	return (0);
}
