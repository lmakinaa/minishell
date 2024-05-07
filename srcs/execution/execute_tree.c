/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/07 20:48:07 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../includes/minishell.h"

int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root)
{
	t_command	*command;

	if (!root)
		return (0);
	if (execute_tree(session, env, root->left) == -1)
		return (-1);
	if (execute_tree(session, env, root->right) == -1)
		return (-1);
	if (root->command)
	{
		if (tokenize_part2(root->command) == -1)
			return (-1);
		if (expander(session, env, root->command) == -1)
			return (-1);
		command = parse_cmd(session, env, root->command);
		if (!command)
			return (-1);
		execute_command(command);
		print_command_elements(command);
	}
	return (0);
}
