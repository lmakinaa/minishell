/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmakina <lmakina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:18:50 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/03 21:23:51 by lmakina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	check_option(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	while (s[++i])
		if (s[i] != 'n')
			return (0);
	return (1);
}

int	b_echo(char **args)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	while (args[i] && check_option(args[i]) == 1)
	{
		option = 1;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (option == 0)
		write(1, "\n", 1);
	return (0);
}
