/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:24:28 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/16 10:25:11 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	set_status(t_lenv *env, int status)
{
	env->exit_status = status;
}

static char	*check_path(t_memsession *session, t_splitdata *d, char *cmd)
{
	char	*s;
	char	**dirs;

	if (!d || !d->words)
		return (NULL);
	dirs = d->words;
	while (*dirs)
	{
		s = ft_joinchar(session, *dirs, '/');
		s = ft_strjoin(session, s, cmd);
		if (access(s, F_OK) == 0)
			return (s);
		dirs++;
	}
	return (NULL);
}

int	get_path(t_command *command)
{
	char		*p;
	char		*cmd;
	t_splitdata	*dirs;

	cmd = command->args[0];
	if (is_builtin(cmd))
		return (0);
	if (ft_strchr(cmd, '/'))
		command->path = cmd;
	p = get_env(command->env, "PATH");
	if (!p)
		if (access(cmd, F_OK) == -1)
			return (set_status(command->env, 1),
				throw_error(cmd, 0, 0, THROW_PERROR), -1);
	dirs = ft_split(command->session, p, ":");
	p = check_path(command->session, dirs, cmd);
	if (!((command->path && !access(command->path, F_OK)) || p))
		return (set_status(command->env, 1),
			throw_error(cmd, 0, 0, THROW_PERROR), -1);
	if (p)
		command->path = p;
	p = ft_strchr(p, '/');
	while (p && p++)
		(1) && (command->args[0] = p, p = ft_strchr(p, '/'));
	return (0);
}
