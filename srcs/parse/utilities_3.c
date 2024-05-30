/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:52:57 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/30 22:44:38 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
			return (throw_error(SYNTAX_ERR, ")", SYNTAX_ERR_LEN, 1), 1);
	}
	if (close != open)
		return (throw_error("due to an unclosed parenthesis", 0, 30, 1), 1);
	return (0);
}

int	are_quotes_closed(char *s)
{
	int		i;
	char	tmp;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			tmp = s[i++];
			while (s[i] && s[i] != tmp)
				i++;
			if (!s[i])
				return (throw_error("due to an unclosed quote", 0, 24, 1), 1);
		}
	}
	return (0);
}

t_lenv	*ft_initialise(t_memsession **session1, t_memsession **session2,
	char **argv, char **envp)
{
	t_lenv			*env;

	(void) argv;
	if (!isatty(STDIN_FILENO))
		exit_on_error("minishell: this tty is not valid\n", 33);
	session_init(session1);
	session_init(session2);
	env = envs_init(*session2, envp);
	(*session1)->envs = env;
	reset_terminal(env);
	return (env);
}

void	end_sessions(t_memsession **s1, t_memsession **s2)
{
	t_lenv	*env;
	int		i;

	env = (*s1)->envs;
	if (env && env->created_files)
	{
		i = -1;
		while (env->created_files[++i])
			unlink(env->created_files[i]);
	}
	env->created_files = NULL;
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
