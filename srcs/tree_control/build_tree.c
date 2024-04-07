/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:33:37 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/07 00:31:38 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

// needs a lot of fixing (almost remake)

t_tnode	*build_tree(t_memsession *session, t_token **tokens, int min_precedence)
{
	if (tokens == NULL || *tokens == NULL)
        return NULL;
		
    t_tnode	*left = create_node(session, 0, *tokens, &tokens);
    
    while (*tokens && get_precedence(*tokens) >= min_precedence)
    {
        t_token *op = *tokens;
        tokens++;
        t_tnode *right = build_tree(session, tokens, get_precedence(*tokens) + 1);
        t_tnode	*new_node = create_node(session, 1, op, &tokens);
        new_node->left = left;
        new_node->right = right;
        left = new_node;
    }
    return (left);
}
