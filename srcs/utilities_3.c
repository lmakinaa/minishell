/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:52:57 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/25 02:02:05 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	are_parenthesis_closed(char *s)
{
	int	i;
	int	open;
	int	close;

	i = -1;
	open = 0;
	close = 0;
	while (s[++i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
			close++;
		if (close > open)
			return (syntax_error("related to parentheses", 22), 1);
	}
	if (close != open)
		return (syntax_error("related to parentheses", 22), 1);
	return (0);
}

int	are_quotes_closed(char *s)
{
	int		i;
	int		open;
	char	tmp;

	i = -1;
	open = 0;
	while (s[++i])
	{
		open = 0;
		if (s[i] == '\'' || s[i] == '"')
		{
			open = 1;
			tmp = s[i++];
			while (s[i] && s[i] != tmp)
				i++;
			if (!s[i])
				return (syntax_error("related to quotes", 17), 1);
		}
	}
	return (0);
}

t_lenv	*ft_initialise(t_memsession **session1, t_memsession **session2,
	int argc, char **argv, char **envp)
{
	t_lenv			*env;

	(void) argv;
	(void) argc;
	session_init(session1);
	session_init(session2);
	env = envs_init(*session2, envp);
	add_env(*session2, env, "tt", "ls -a");
	return (env);
}

void	end_sessions(t_memsession **s1, t_memsession **s2)
{
	session_destroy(s1);
	session_destroy(s2);
}

int	is_sep(char c, char *seps)
{
	int	i;

	i = -1;
	while (seps[++i])
		if (seps[i] == c)
			return (1);
	return (0);
}
