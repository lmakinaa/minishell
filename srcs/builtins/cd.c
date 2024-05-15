/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:18:51 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/15 21:40:30 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	go_home(t_lenv *env)
{
	char	*home;

	add_env(env->session, env, "OLDPWD", get_env(env, "PWD"));
	home = get_env(env, "HOME");
	if (!home)
		return (throw_error("cd: HOME not set", 0, 16, 0), 1);
	if (chdir(home) == 0)
	{
		add_env(env->session, env, "OLDPWD", get_env(env, "PWD"));
		return (add_env(env->session, env, "PWD", home), 0);
	}
	return (1);
}

static int	dump_err(char *arg)
{
	write(2, "minishell: cd: `", 16);
	write(2, arg, ft_strlen(arg));
	write(2, "': No such file or directory\n", 29);
	return (127);
}

int	b_cd(t_command *command)
{
	char	*cwd;
	char	*dest;

	cwd = getcwd(NULL, 0);
	add_to_session(command->env->session, cwd);
	if (command->argc != 2)
		return (go_home(command->env));
	if (chdir(command->args[1]) != 0)
		return (dump_err(command->args[1]));
	dest = getcwd(NULL, 0);
	add_env(command->env->session, command->env, "OLDPWD", get_env(command->env, "PWD"));
	if (!dest)
		perror("getcwd");
	add_env(command->env->session, command->env, "PWD",
		ft_strdup(command->env->session, dest, ft_strlen(dest)));
	return (0);
}
