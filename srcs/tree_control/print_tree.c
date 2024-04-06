/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:40:50 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 22:02:21 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void print_tree(t_tnode *node, int space)
{
    int i;

    if (node == NULL) {
        return;
    }

    space += 10;

    print_tree(node->right, space);

    printf("\n");
    for (i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%s\n", node->token->value);

    print_tree(node->left, space);
}
