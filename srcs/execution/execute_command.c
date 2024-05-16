/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:43:55 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/16 16:02:53 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	exec_binary(t_command *cmd)
{
	pid_t	pid;
	int		s;

	pid = fork();
	if (!pid)
	{
		if (execve(cmd->path, cmd->args, generate_env_array(cmd->session, cmd->env)) == -1)
			return (set_status(cmd->env, 126),
			throw_error(cmd->path, 0, 0, THROW_PERROR));
	}
	//else if (pid == -1)
	else
	{
		waitpid(pid, &s, 0);
		cmd->env->exit_status = s;
	}
	// this is just for test
}

t_command	*expand_n_generate_cmd(t_memsession *session, t_lenv *env,
	t_token **node)
{
	t_command	*cmd;

	if (tokenize_part2(node) == -1 || expander(session, env, node) == -1)
	{
		env->exit_status = 1;
		return (NULL);
	}
	cmd = parse_cmd(session, env, node);
	return(cmd);
}

void	exec_builtin(t_command *command)
{
	if (!ft_strcmp(0, command->args[0], "echo"))
		command->env->exit_status = b_echo(command->args);
	else if (!ft_strcmp(0, command->args[0], "pwd"))
		command->env->exit_status = b_pwd();
	else if (!ft_strcmp(0, command->args[0], "export"))
		command->env->exit_status = b_export(command->env, command->args);
	else if (!ft_strcmp(0, command->args[0], "cd"))
		command->env->exit_status = b_cd(command);
	else if (!ft_strcmp(0, command->args[0], "env"))
		command->env->exit_status = b_env(command);
	else if (!ft_strcmp(0, command->args[0], "unset"))
		command->env->exit_status = b_unset(command);
	else if (!ft_strcmp(0, command->args[0], "exit"))
		command->env->exit_status = b_exit(command);
}

int	execute_command(t_memsession *session, t_lenv *env,
	t_token **tokens, int pip)
{
	int			backup_fds[2];
	int			s;
	t_command	*command;

	(void) pip;
	command = expand_n_generate_cmd(session, env, tokens);
		if (!command)
			return (-1);
	backup_fds[0] = dup(0);
	backup_fds[1] = dup(1);
	s = out_redirect(command->output_files, command->output_redir_type);
	if (s)
		env->exit_status = s;
	if (!command->args)
		return (reset_fds(backup_fds), 0);
	if (is_builtin(command->args[0]))
		exec_builtin(command);
	else
		exec_binary(command);
	return (reset_fds(backup_fds));
}
