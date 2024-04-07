/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:40:50 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 22:52:55 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	print_node_value(t_tnode *node)
{
	int	i;

	i = -1;
	if (node->operator)
		printf("%s", node->operator->value);
	else if (node->command)
	{
		while (node->command[++i])
			printf("%s ", node->command[i]->value);
		printf("\n");
	}
}

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
	print_node_value(node);

    print_tree(node->left, space);
}
