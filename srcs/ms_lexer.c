/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:04:32 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/16 15:38:07 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/*
* In this part we identifie the operators specefically 
*/
t_token	**tokenize_part_1(t_memsession *session, t_splitdata *splited_cmd)
{
	int		i;
	t_token	**toks;

	toks = session_malloc(session,
			(splited_cmd->word_count + 1) * sizeof(t_token *), 0);
	i = -1;
	while (++i < splited_cmd->word_count)
	{
		toks[i] = session_malloc(session, sizeof(t_token), 0);
		toks[i]->tokens_nbr = splited_cmd->word_count;
		toks[i]->order = i;
		toks[i]->value = splited_cmd->words[i];
		toks[i]->is_operator = new_is_ops(splited_cmd->words[i]);
		toks[i]->len = ft_strlen(splited_cmd->words[i]);
		toks[i]->type = get_token_type(splited_cmd->words[i],
				toks[i]->is_operator);
		toks[i]->command = 1;
	}
	toks[i] = NULL;
	i = -1;
	while (++i < toks[0]->tokens_nbr)
		if (toks[i]->type != T_WORD && !is_redirector(*(toks[i]))
			&& toks[i]->type != T_PARENTHESIS_COMMAND && toks[i]->is_operator)
			toks[i]->command = 0;
	return (toks);
}

t_token	**ms_lexer(t_memsession *session, char *command)
{
	t_token		**res;
	t_splitdata	*splited_cmd;

	splited_cmd = advanced_split(session, command, SEPERATORS);
	if (!splited_cmd->word_count)
		return (NULL);
	res = tokenize_part_1(session, splited_cmd);
	// syntax_analyze_1()
	return (res);
}
