/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:24:49 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/11 05:56:54 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	dump_err(char *name)
{
	write(2, "minishell: unset: `", 19);
	write(2, name, ft_strlen(name));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	b_unset(t_command *command)
{
	int	i;
	int	err;
	int	nothing;

	if (command->argc == 1)
		return (0);
	err = 0;
	i = 1;
	while (command->args[i])
	{
		if (!check_identifier(command->args[i], &nothing))
		{
			dump_err(command->args[i]);
			err = 1;
		}
		else
			remove_env(command->env->session, command->env, command->args[i]);
		i++;
	}
	return (err);
}
