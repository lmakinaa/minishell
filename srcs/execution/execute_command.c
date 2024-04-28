/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:43:55 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/28 14:52:20 by ijaija           ###   ########.fr       */
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
}

int	execute_command(t_command *command)
{
	if (is_builtin(command->args[0]))
		exec_builtin(command);
	return (0);
}
