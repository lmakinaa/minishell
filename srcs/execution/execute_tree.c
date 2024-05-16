/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/16 16:03:12 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static void	ft_exec_pipe_child(t_tnode *node, int pfds[2], int direction)
{
	if (direction == 0)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else if (direction == 1)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	execute_command(node->session, node->env, node->command, 1);
	// 5asni nfree child process
	exit(node->env->exit_status);
}

static int	exec_pipes(t_tnode *tree)
{
	int	p_left;
	int	fds[2];
	int	p_right;
	int	status;

	pipe(fds);
	p_left = fork();
	if (!p_left)
		ft_exec_pipe_child(tree->left, fds, 0);
	else
	{
		p_right = fork();
		if (!p_right)
			ft_exec_pipe_child(tree->right, fds, 1);
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(p_left, &status, 0);
			waitpid(p_right, &status, 0);
			return (status);
		}
	}
	return (1);
}

int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root, int pip)
{
	if (!root)
		return (0);
	if (root->operator && root->operator->type == T_PIPE)
		return (exec_pipes(root), 0);
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
