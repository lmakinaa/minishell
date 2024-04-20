/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:12:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/20 22:19:50 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	is_sep(char c, char *seps)
{
	int	i;

	i = -1;
	while (seps[++i])
		if (seps[i] == c)
			return (1);
	return (0);
}

char	*z_strdup(t_memsession *session, char **str, char *seps)
{
	int		i;
	int		j;
	char	*res;
	char	*s;
	char	*resaddr;
	
	i = -1;
	s = *str;
	while (s[++i] && !is_sep(s[i], seps))
		;
	res = session_malloc(session, (i + 1) * sizeof(char), 0);
	resaddr = res;
	j = 0;
	while (j < i)
	{
		*res = s[j];
		res++;
		j++;
	}
	*res = '\0';
	(*str) += j;
	return (resaddr);
}

int	var_expansion(t_memsession *session, t_lenv *env, t_token *token)
{
	int		i;
	char	*str;
	char	*var;
	
	str = token->value;
	i = -1;
	while (*str)
	{
		if (*(str++) == '$')
		{
			if (*str == '$')
				return (syntax_error("(special vars not supported)", 28), -1);
			else
			{
				var = get_env(env, z_strdup(session, &str, "$'\""));
				str--;
			}
		}
		str++;
	}
	return (0);
}

/*
* Expand Vars and whats inside quotes and remove quotes
*/
int	expander(t_memsession *session, t_lenv *env, t_token **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN)
		{
			if (var_expansion(session, env, cmd[i]) == -1)
				return (-1);
		}
	}
	return (0);
}