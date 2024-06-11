/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtalbi <mtalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 22:19:01 by mtalbi            #+#    #+#             */
/*   Updated: 2024/06/08 18:06:06 by mtalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	b_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (perror("getcwd"), -1);
	if (write(1, cwd, ft_strlen(cwd)) == -1)
		return (free(cwd), -1);
	if (write(1, "\n", 1) == -1)
		return (free(cwd), -1);
	free(cwd);
	return (0);
}
