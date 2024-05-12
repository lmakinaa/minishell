/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:43:55 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/12 03:47:46 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	exec_builtin(t_command *command)
{
	if (!ft_strcmp(command->args[0], "echo"))
		b_echo(command->args);
	else if (!ft_strcmp(command->args[0], "pwd"))
		b_pwd();
	else if (!ft_strcmp(command->args[0], "export"))
		b_export(command->env, command->args);
	else if (!ft_strcmp(command->args[0], "cd"))
		b_cd(command);
	else if (!ft_strcmp(command->args[0], "env"))
		b_env(command);
	else if (!ft_strcmp(command->args[0], "unset"))
		b_unset(command);
	else if (!ft_strcmp(command->args[0], "exit"))
		b_exit(command);
}

int	execute_command(t_command *command)
{
	int	backup_fds[2];

	backup_fds[0] = dup(0);
	backup_fds[1] = dup(1);
	out_redirect(command->output_files, command->output_redir_type);
	if (!command->args)
		return (reset_fds(backup_fds), 0);
	if (is_builtin(command->args[0]))
		exec_builtin(command);
	//else
	//	exec_binary(command);
	return (reset_fds(backup_fds));
}
