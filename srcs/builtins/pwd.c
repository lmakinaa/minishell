/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:19:01 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/28 14:49:39 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	b_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		exit_on_error("getcwd() failed", 15);
	if (write(1, cwd, ft_strlen(cwd)) == -1)
		return (free(cwd), -1);
	if (write(1, "\n", 1) == -1)
		return (free(cwd), -1);
	free(cwd);
	return (0);
}
