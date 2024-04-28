/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:18:51 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/28 15:12:49 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	ft_cd_home(void)
{
	char	*home;

	ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
	home = ft_get_envlst_val("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == ENO_SUCCESS)
		return (ft_update_envlst("PWD", home, false), 0);
	return (1);
}

static int	ft_cd_err_msg(char *err_msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	ft_cd(char *path)
{
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (!path)
		return (ft_cd_home());
	if (chdir(path) != 0)
		return (ft_cd_err_msg(path));
	ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
	add_env(command->env->session, command->env, "PWD", cwd);
	return (0);
}
