/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:26:43 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 21:51:25 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	*reading(t_memsession *session, int fd, char *stock)
{
	char	*buffer;
	int		readed;

	readed = 1;
	while (!ft_strchr(stock, '\n') && readed != 0)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (exit_on_error(MALLOC_ERR, 23), NULL);
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
		{
			free(buffer);
			if (stock)
				del_from_session(session, stock);
			return (NULL);
		}
		if (readed == 0)
			return (free(buffer), stock);
		buffer[readed] = '\0';
		stock = custom_strjoin(session, stock, buffer);
		free(buffer);
	}
	return (stock);
}

char	*cleaning(t_memsession *session, char *stock)
{
	int		i;
	int		j;
	char	*new_stock;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		return (del_from_session(session, stock), NULL);
	new_stock = session_malloc(session,
		(ft_strlen(stock) - i + 1) * sizeof(char), 0);
	if (!new_stock)
		return (del_from_session(session, stock), NULL);
	i++;
	j = 0;
	while (stock[i])
		new_stock[j++] = stock[i++];
	new_stock[j] = '\0';
	del_from_session(session, stock);
	return (new_stock);
}

char	*get_next_line(t_memsession *session, int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (!stock || (stock && !ft_strchr(stock, '\n')))
		stock = reading(session, fd, stock);
	if (!stock)
		return (NULL);
	line = line_fill(session, stock);
	if (!line)
	{
		del_from_session(session, stock);
		stock = NULL;
		return (NULL);
	}
	stock = cleaning(session, stock);
	return (line);
}
