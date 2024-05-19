/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/19 18:29:19 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

// 5asni nfree child process
static void	exec_child(t_tnode *node, int pfds[2], int what_child)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(node->env->initial_termios));
	if (what_child == LEFT_C)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else if (what_child == RIGHT_C)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	exit(execute_tree(node->session, node->env, node, 1));
}

int	ft_get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
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
		exec_child(tree->left, fds, LEFT_C);
	else
	{
		p_right = fork();
		if (!p_right)
			exec_child(tree->right, fds, RIGHT_C);
		else
		{
			close(fds[0]);
			close(fds[1]);
			waitpid(p_left, &status, 0);
			waitpid(p_right, &status, 0);
			return (ft_get_exit_status(status));
		}
	}
	return (1);
}

int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root, int pip)
{
	if (!root)
		return (0);
	if (root->operator && root->operator->type == T_PIPE)
		return (s_s(env, exec_pipes(root)));
	else if (root->operator)
	{
		if (root->operator->type == T_AND)
		{
			env->exit_status = execute_tree(session, env, root->left, 0);
			if (env->exit_status == 0)
				return (s_s(env, execute_tree(session, env, root->right, 0)));
		}
		else if (root->operator->type == T_OR)
		{
			env->exit_status = execute_tree(session, env, root->left, 0);
			if (env->exit_status == 0)
				return (0);
			return (s_s(env, execute_tree(session, env, root->right, 0)));
		}
	}
	else if (root->command)
		return (s_s(env, execute_command(session, env, root->command, pip)));
	return (env->exit_status);
}
