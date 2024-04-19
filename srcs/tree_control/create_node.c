/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:03:17 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 15:54:38 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_token	**compose_command(t_memsession *session, t_token ***t)
{
	t_token	**tokens;
	t_token	**res;
	int		i;
	int		j;

	tokens = *t;
	i = -1;
	while (tokens[++i])
		if (!tokens[i]->command)
			break ;
	res = session_malloc(session, (i + 1) * sizeof(t_token), 0);
	j = -1;
	while (++j < i)
		res[j] = tokens[j];
	res[j] = NULL;
	(*t) += j;
	return (res);
}

t_tnode	*create_node(t_memsession *session, int op,
	t_token *token, t_token ***tokens)
{
	t_tnode	*res;

	res = session_malloc(session, sizeof(t_tnode), 0);
	if (op)
	{
		res->operator = token;
		res->command = NULL;
	}
	else if (token->type == T_PARENTHESIS_COMMAND)
		return (nested_tree(session, tokens));
	else
	{
		res->operator = NULL;
		res->command = compose_command(session, tokens);
	}
	res->left = NULL;
	res->parsed_cmd = NULL;
	res->right = NULL;
	return (res);
}
