/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/13 01:20:49 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

//int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root)
//{
//	t_command	*command;

//	if (!root)
//		return (0);
//	if (execute_tree(session, env, root->left) == -1)
//		return (-1);
//	if (execute_tree(session, env, root->right) == -1)
//		return (-1);
//	if (root->command)
//	{
//		command = expand_n_generate_cmd(session, env, root->command);
//		if (!command)
//			return (-1);
//		execute_command(command);
//		//print_command_elements(command);
//	}
//	return (0);
//}

int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root, int pip)
{
	if (!root)
		return (0);
	//if (root->operator->type == T_PIPE)
	//	return (exec_pipes(), 0);
	if (root->operator)
	{
		if (root->operator->type == T_AND)
		{
			execute_tree(session, env, root->left, 0);
			if (env->exit_status == 0)
				return (execute_tree(session, env, root->right, 0));
		}
		else if (root->operator->type == T_OR)
		{
			execute_tree(session, env, root->left, 0);
			if (env->exit_status == 0)
				return (0);
			return (execute_tree(session, env, root->right, 0));
		}
	}
	else if (root->command)
		execute_command(session, env, root->command, pip);
	return (0);
}
