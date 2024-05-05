/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:12:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/05 23:28:18 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*var_expansion(t_memsession *session, t_lenv *env, char **str)
{
	char	*new_value;
	char	*var;

	new_value = ft_strdup(session, "", 0);
	while (**str && **str != '"')
	{
		if (**str && **str != '$')
			new_value = ft_joinchar(session, new_value, *((*str)++));
		else if (**str && **str == '$')
		{
			if (*((*str) + 1) && *((*str) + 1) == '?' && (*str)++ && (*str)++)
				new_value = ft_strjoin(session, new_value, get_exit_status(session, env));
			else if (*((*str) + 1) && *((*str) + 1) != '$' && (*str)++)
			{
				var = get_env(env, var_name_strdup(session, str));
				new_value = ft_strjoin(session, new_value, var);
			}
			else if (**str && **str != '"')
				new_value = ft_joinchar(session, new_value, *((*str)++));
		}
	}
	return (new_value);
}

char	*expand_2(t_memsession *session, char *str)
{
	char	*res;
	char	*s;

	res = ft_strdup(session, "", 0);
	while (*str)
		if (*str && (*str == '\'' || *str == '"'))
		{
			res = ft_joinchar(session, res, *str);
			if (*str && *str == '\'' && str++)
				res = ft_strjoin(session, res, z_strdup(session, &str, "'"));
			else if (*str && *str == '"' && str++)
				res = ft_strjoin(session, res, z_strdup(session, &str, "\""));
		}
		else if (*str)
			res = ft_joinchar(session, res, *(str++));
	s = no_quotes(session, res, 1);
	if (ft_strchr(s, 127))
	{
		s = expand_wildcard(session, s);
		if (s)
			return (s);
	}
	return (res);
}

char	*expand_1(t_memsession *session, t_lenv *env, char *str)
{
	char	*res;
	char	*tmp;

	tmp = str;
	res = ft_strdup(session, "", 0);
	while (*str)
		if (*str == '\'')
		{
			res = ft_joinchar(session, res, *(str++));
			res = ft_strjoin(session, res, z_strdup(session, &str, "'"));
			res = ft_joinchar(session, res, *(str++));
		}
		else if (*str == '"')
		{
			res = ft_joinchar(session, res, *(str++));
			res = ft_strjoin(session, res, var_expansion(session, env, &str));
			res = ft_joinchar(session, res, *(str++));
		}
		else if (*str)
			res = ft_strjoin(session, res, var_expansion(session, env, &str));
	return (del_from_session(session, tmp), res);
}

/*
* Expand Vars and whats inside quotes and remove quotes
*/
int	expander(t_memsession *session, t_lenv *env, t_token **cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN || cmd[i]->type == T_INPUT_FILE
			|| cmd[i]->type == T_OUTPUT_FILE)
		{
			cmd[i]->value = expand_1(session, env, cmd[i]->value);
			//puts(cmd[i]->value);
			cmd[i]->value = expand_2(session, cmd[i]->value);
		}
		if (cmd[i]->type == T_INPUT_FILE || cmd[i]->type == T_OUTPUT_FILE)
			if (ft_countword(cmd[i]->value, SEPERATORS) > 1)
				return (throw_error("ambiguous redirect", 18, 0), -1);
	}
	return (0);
}
