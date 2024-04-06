/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:40:50 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 18:44:31 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void print_ast(t_tnode* node, int depth)
{
    if (node == NULL) {
        return;
    }

    // Print right subtree first, with increased depth
    print_ast(node->right, depth + 1);

    // Print the current node
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    if (node->token != NULL) {
        printf("%s\n", node->token->value);
    }

    // Print left subtree, with increased depth
    print_ast(node->left, depth + 1);
}
