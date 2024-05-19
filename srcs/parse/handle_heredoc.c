/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:32:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/19 03:22:53 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	free_line(int exp, char *ptr)
{
	if (!exp)
		free(ptr);
	return (1);
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

static char	*expand_var(t_memsession *s, char *str)
{
	char	*res;
	char	*tmp;
	char	*var;

	tmp = str;
	res = NULL;
	while (*tmp)
	{
		res = ft_strjoin(s, res, z_strdup(s, &tmp, "$"));
		if (*tmp && *tmp == '$')
		{
			tmp++;
			if (*tmp == '?' && tmp++)
				var = get_exit_status(s, s->envs);
			else
				var = get_env(s->envs, var_name_strdup(s, &tmp));
			res = ft_strjoin(s, res, var);
		}
	}
	free(str);
	return (res);
}

int	handle_heredoc(t_memsession *session, t_token *tok)
{
	char	*line;
	char	*eol;
	int		fd;
	int		exp;

	(1) && (eol = tok->value, exp = 1);
	(ft_strchr(eol, '"') || ft_strchr(eol, '\'')) && (exp = 0);
	fd = create_random_file(session, tok, "0123456789abcdef");
	while (1)
	{
		line = readline("# ");
		if (!line)
			break ;
		(exp) && (line = expand_var(session, line));
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		if (!ft_strcmp(1, line, no_quotes(session, eol, 0)) && free_line(exp, line))
			break ;
		(!exp) && (free(line), 0);
	}
	tok->type = T_STD_INPUT;
	close(fd);
	return (0);
}
