/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:33:37 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/16 16:45:16 by ijaija           ###   ########.fr       */
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
	res->session = session;
	res->env = session->envs;
	return (res);
}

int	is_binop(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_AND || token->type == T_OR || token->type == T_PIPE)
		return (1);
	return (0);
}

t_tnode	*build_tree(t_memsession *session, t_token ***tokens,
	int min_precedence)
{
	t_tnode	*right;
	t_tnode	*left;
	t_token	*op;
	t_tnode	*new_node;

	if (*tokens == NULL || **tokens == NULL)
		return (NULL);
	left = create_node(session, 0, **tokens, tokens);
	while (is_binop(**tokens) && get_precedence(**tokens) >= min_precedence)
	{
		op = **tokens;
		(*tokens)++;
		//right = build_tree(session, tokens, get_precedence(op) + 1);
		right = build_tree(session, tokens, get_precedence(op));
		if (!right)
			return (left);
		new_node = create_node(session, 1, op, tokens);
		new_node->left = left;
		new_node->right = right;
		left = new_node;
		if (!left)
			return (NULL);
	}
	return (left);
}
