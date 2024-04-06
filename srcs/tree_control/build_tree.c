/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:33:37 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 18:53:36 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

// should be fixed
t_tnode	*build_tree(t_memsession *session, t_token **tokens, int min_precedence)
{
    t_tnode	*left = create_node(session, *tokens);
    (*tokens)++;
    
    while (get_precedence(**tokens) >= min_precedence)
    {
        t_token *op = *tokens;
        (*tokens)++;
        t_tnode *right = build_tree(session, tokens, get_precedence(**tokens) + 1);
        t_tnode	*new_node = create_node(session, op);
        new_node->left = left;
        new_node->right = right;
        left = new_node;
    }
    return (left);
}
