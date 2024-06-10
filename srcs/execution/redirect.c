/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:23:15 by mtalbi            #+#    #+#             */
/*   Updated: 2024/06/10 16:25:25 by ijaija           ###   ########.fr       */
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

int	in_redirect(char *input_file)
{
	int	fd_in;

	if (!input_file)
		return (0);
	fd_in = open(input_file, O_RDONLY, 0644);
	if (fd_in == -1)
		return (throw_error(input_file, 0, 0, THROW_PERROR), 1);
	else
	{
		if (dup2(fd_in, 0) == -1)
			return (close(fd_in),
				throw_error(input_file, 0, 0, THROW_PERROR), 1);
		close(fd_in);
	}
	return (0);
}
