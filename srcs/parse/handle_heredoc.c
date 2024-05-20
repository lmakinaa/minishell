/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:32:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/20 18:06:56 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	free_line(char *ptr)
{
	free(ptr);
	return (1);
}

int	create_random_file(t_memsession *s, t_token *tok, char *base)
{
	int		fd;
	int		readed;
	char	*random;
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		exit_on_error("open() failed\n", 14);
	random = session_malloc(s, 17 * sizeof(char), 0);
	readed = read(fd, random, 16);
	if (readed < 0)
		exit_on_error("read() failed\n", 14);
	(1) && (random[readed] = '\0', i = -1);
	while (++i < readed)
		random[i] = base[((unsigned char) random[i]) % 16];
	if (close(fd) == -1)
		exit_on_error("open() failed\n", 14);
	tok->value = ft_strdup(s, "/tmp/", 5);
	tok->value = ft_strjoin(s, tok->value, random);
	fd = open(tok->value, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		exit_on_error("open() failed\n", 14);
	s->envs->created_files = append_arg(s, s->envs->created_files,
			tok->value, 0);
	return (fd);
}

static int	is_identif2(char c)
{
	return (ft_isalpha(c) || c == '?' || c == '_');
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
		if (*tmp && *tmp == '$' && is_identif2(*(tmp + 1)))
		{
			tmp++;
			if (*tmp == '?' && tmp++)
				var = get_exit_status(s, s->envs);
			else
				var = get_env(s->envs, var_name_strdup(s, &tmp));
			res = ft_strjoin(s, res, var);
		}
		else if (*tmp)
			res = ft_joinchar(s, res, *(tmp++));
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
	int		sec_fd;

	(1) && (sec_fd = dup(0), eol = tok->value, exp = 1, g_sig = 2);
	(ft_strchr(eol, '"') || ft_strchr(eol, '\'')) && (exp = 0);
	fd = create_random_file(session, tok, "0123456789abcdef");
	while (1)
	{
		line = readline("# ");
		if (!line)
			break ;
		if (!ft_strcmp(1, line, no_quotes(session, eol, 0)) && free_line(line))
			break ;
		(exp) && (line = expand_var(session, line));
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		(!exp) && (free(line), 0);
	}
	tok->type = T_STD_INPUT;
	(g_sig == 3) && (s_s(session->envs, 128 + SIGINT));
	(1) && (g_sig = 0, close(fd), dup2(sec_fd, 0), close(sec_fd));
	return (0);
}
