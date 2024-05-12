/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/12 18:28:00 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_command	*expand_n_generate_cmd(t_memsession *session, t_lenv *env,
	t_token **node)
{
	if (tokenize_part2(node) == -1)
		return (NULL);
	if (expander(session, env, node) == -1)
		return (NULL);
	return(parse_cmd(session, env, node));
}

int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root)
{
	t_command	*command;

	if (!root)
		return (0);
	if (execute_tree(session, env, root->left) == -1)
		return (-1);
	if (execute_tree(session, env, root->right) == -1)
		return (-1);
	//if (root->operator)
	//	printf("%d\n", root->operator->type);
	if (root->command)
	{
		command = expand_n_generate_cmd(session, env, root->command);
		if (!command)
			return (-1);
		execute_command(command);
		//print_command_elements(command);
	}
	return (0);
}

//int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root)
//{
//	t_command	*command;

//	if (!root)
//		return (0);
//	if (root->)
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
