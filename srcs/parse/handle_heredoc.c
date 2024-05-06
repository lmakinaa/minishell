/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:32:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/06 19:36:46 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	free_line(char *ptr)
{
	return (free(ptr), 1);
}

int	create_random_file(t_memsession *session, t_token *tok, char *base)
{
	int		fd;
	int		readed;
	char	*random;
	int		i;
	
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		exit_on_error("open() failed\n", 14);
	random = session_malloc(session, 17 * sizeof(char), 0);
	readed = read(fd, random, 16);
	if (readed < 0)
		exit_on_error("read() failed\n", 14);
	random[readed] = '\0';
	i = -1;
	while (++i < readed)
		random[i] = base[((unsigned char) random[i]) % 16];
	if (close(fd) == -1)
		exit_on_error("open() failed\n", 14);
	tok->value = ft_strdup(session, "/tmp/", 5);
	tok->value = ft_strjoin(session, tok->value, random);
	fd = open(tok->value, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		exit_on_error("open() failed\n", 14);
	return (fd);
}

int	handle_heredoc(t_memsession *session, t_token *tok)
{
	char	*line;
	char	*eol;
	int		fd;

	eol = tok->value;
	fd = create_random_file(session, tok, "0123456789abcdef");
	while (1)
	{
		line = readline("# ");
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		if (!ft_strcmp(line, no_quotes(session, eol, 0)) && free_line(line))
			break;
		free(line);
	}
	tok->type = T_STD_INPUT;
	close(fd);
	return (0);
}
