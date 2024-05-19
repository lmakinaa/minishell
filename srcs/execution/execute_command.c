/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:43:55 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/19 16:59:43 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

// it needs more work
int	exec_binary(t_command *cmd)
{
	pid_t	pid;
	int		s;

	pid = fork();
	if (!pid)
	{
		if (execve(cmd->path, cmd->args,
				generate_env_array(cmd->session, cmd->env)) == -1)
			(throw_error(cmd->path, 0, 0, THROW_PERROR), exit(126));
	}
	else if (pid == -1)
		exit_on_error("fork() failed\n", 14);
	waitpid(pid, &s, 0);
	return (ft_get_exit_status(s));
}

int	exec_builtin(t_command *command)
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
	return (command->env->exit_status);
}

// The expand_n_generate_cmd() function is the last part of parsing
int	execute_command(t_memsession *session, t_lenv *env,
	t_token **tokens, int pip)
{
	int			backup_fds[2];
	int			s;
	t_command	*command;

	(void) pip;
	g_sig = 1;
	command = expand_n_generate_cmd(session, env, tokens);
	if (!command)
		return (env->exit_status);
	(1) && (backup_fds[0] = dup(0), backup_fds[1] = dup(1));
	if (in_redirect(command->input_file)
		|| out_redirect(command->output_files, command->output_redir_type))
		return (reset_fds(backup_fds, pip), 1);
	if (!command->args)
		return (reset_fds(backup_fds, pip), 0);
	if (is_builtin(command->args[0]))
		s = exec_builtin(command);
	else
		s = exec_binary(command);
	return (reset_fds(backup_fds, pip), s);
}
