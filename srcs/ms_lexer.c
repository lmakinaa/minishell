/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:04:32 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 17:31:47 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/*
* In this part we identifie the operators specefically 
*/
t_token	*tokenize_part_1(t_memsession *session, t_splitdata *splited_cmd)
{
	int		i;
	t_token	*tokens;

	tokens = session_malloc(session,
		splited_cmd->word_count * sizeof(t_token), 0);
	i = -1;
	while (++i < splited_cmd->word_count)
	{
		tokens[i].tokens_nbr = splited_cmd->word_count;
		tokens[i].order = i;
		tokens[i].value = splited_cmd->words[i];
		tokens[i].is_operator = new_is_ops(splited_cmd->words[i]);
		tokens[i].len = ft_strlen(splited_cmd->words[i]);
		tokens[i].type = get_token_type(splited_cmd->words[i], tokens[i].is_operator);
		tokens[i].command = 1;
		tokens[i].right = NULL;
		tokens[i].left = NULL;
	}
	i = -1;
	while (++i < tokens[0].tokens_nbr)
		if (tokens[i].is_operator && !is_redirector(tokens[i])
			&& tokens[i].type != T_PARENTHESIS_COMMAND)
			tokens[i].command = 0;
	return (tokens);
}

t_token	*ms_lexer(t_memsession *session, char *command)
{
	t_token		*res;
	t_splitdata	*splited_cmd;

	splited_cmd = advanced_split(session, command, SEPERATORS);
	if (!splited_cmd->word_count)
		return (NULL);
	res = tokenize_part_1(session, splited_cmd);
	return (res);
}
