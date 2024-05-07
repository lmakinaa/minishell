/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:23:15 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/07 19:11:31 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	out_redirect(char **out, char *types)
{
	int	fd_out;
	int	i;

	i = 0;
	while (out && out[i])
	{
		if (types[i] == T_APPEND_REDIR)
			fd_out = open(out[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd_out = open(out[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd_out == -1)
			return (throw_error(out[i], 0, 0, THROW_PERROR), 1);
		if (out[i + 1])
			close(fd_out);
		else
		{
			if (dup2(fd_out, 1) == -1)
				return (close(fd_out),
					throw_error(out[i], 0, 0, THROW_PERROR), 1);
			close(fd_out);
		}
		i++;
	}
	return (0);
}
