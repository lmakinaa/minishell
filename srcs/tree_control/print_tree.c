/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:40:50 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 23:46:43 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*put_type(int type)
{
	switch (type)
	{
		case T_UNKNOWN:
			return "UNKNOWN";
		case T_APPEND_REDIR:
			return "APPEND_REDIR";
		case T_PARENTHESIS_COMMAND:
			return "PARENTHESIS_COMMAND";
		case T_BUILTIN:
			return "BUILTIN";
		case T_WORD:
			return "WORD";
		case T_PIPE:
			return "PIPE";
		case T_VAR:
			return "VAR";
		case T_AUTOMATIC_VAR:
			return "AUTOMATIC_VAR";
		case T_OR:
			return "OR";
		case T_AND:
			return "AND";
		case T_HERDOC:
			return "HERDOC";
		case T_INPUT_REDIRECTOR:
			return "INPUT_REDIRECTOR";
		case T_OUT_REDIR:
			return "OUT_REDIR";
		case T_OUTPUT_FILE:
			return "OUTPUT_FILE";
		case T_INPUT_FILE:
			return "INPUT_FILE";
		case T_STD_INPUT:
			return "T_STD_INPUT";
		case T_ARG:
			return "T_ARG";
		default:
			return "UNKNOWN";
	}
}

void	print_node_value(t_tnode *node)
{
	int	i;

	i = -1;
	if (node->operator)
		printf("%s", node->operator->value);
	else if (node->command)
	{
		while (node->command[++i])
			printf("[%s]:%s\t", put_type(node->command[i]->type), node->command[i]->value);
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
