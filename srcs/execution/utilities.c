/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:56:03 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/11 06:16:04 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	reset_fds(int backup_fds[])
{
	if (dup2(backup_fds[0], 0) == -1)
		return (throw_error("dup2", 0, 0, THROW_PERROR), 1);
	close(backup_fds[0]);
	if (dup2(backup_fds[1], 1) == -1)
		return (throw_error("dup2", 0, 0, THROW_PERROR), 1);
	close(backup_fds[1]);
	return (0);
}
