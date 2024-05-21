/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:49:45 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/21 03:21:31 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	ft_atoi(char *str, int *buff)
{
	int	sign;

	sign = 1;
	(*buff) = 0;
	while (*str && is_sep(*str, " \t\n"))
		str++;
	if ((*str == '+' || *str == '-') && str++)
		(*(str - 1) == '-') && (sign = -1);
	if (!*str)
		return (-1);
	while (*str && ft_isdigit(*str))
	{
		(*buff) = ((*buff) * 10) + (*str - '0');
		str++;
	}
	if (*str)
		return (-1);
	(*buff) *= sign;
	return (0);
}

static void	dump_output(int t_err, char *arg)
{
	if (t_err == 0)
		return (write(2, "exit\n", 5), void_return());
	else
	{
		write(2, "exit\n", 5);
		if (t_err == 1)
			throw_error("exit: too many arguments\n", 0, 25, 0);
		else if (t_err == 2)
		{
			write(2, "minishell: exit: ", 17);
			write(2, arg, ft_strlen(arg));
			write(2, ": numeric argument required\n", 28);
		}
	}
}

int	b_exit(t_command *cmd, int b_f[])
{
	int				status;
	t_memsession	*env_session;
	t_memsession	*sess;

	if (cmd->argc == 1)
	{
		status = cmd->env->exit_status;
		dump_output(0, NULL);
	}
	else if (ft_atoi(cmd->args[1], &status) == -1)
	{
		status = 255;
		dump_output(2, cmd->args[1]);
	}
	else if (cmd->argc > 2)
		return (dump_output(1, NULL), 1);
	else
		dump_output(0, NULL);
	env_session = cmd->env->session;
	sess = cmd->session;
	rl_clear_history();
	reset_fds(b_f, 0);
	end_sessions(&env_session, &sess);
	exit((unsigned char) status);
	return (0);
}
