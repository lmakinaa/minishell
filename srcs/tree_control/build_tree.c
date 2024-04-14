/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:33:37 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/14 21:18:38 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	is_binop(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_AND || token->type == T_OR || token->type == T_PIPE)
		return (1);
	return (0);
}

t_tnode	*build_tree(t_memsession *session, t_token ***tokens, int min_precedence)
{
	t_tnode *right;
	t_tnode	*left;
	t_token *op;
	t_tnode	*new_node;

	if (*tokens == NULL || **tokens == NULL)
        return NULL;
	left = create_node(session, 0, **tokens, tokens);
    while (is_binop(**tokens) && get_precedence(**tokens) >= min_precedence)
    {
        op = **tokens;
        (*tokens)++;
		if (!(*tokens))
			exit_on_error("Syntax error\n", 13);
        right = build_tree(session, tokens, get_precedence(op) + 1);
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
