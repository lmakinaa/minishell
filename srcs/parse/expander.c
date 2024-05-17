/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:12:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/17 13:33:47 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../includes/minishell.h"

char	*var_expansion(t_memsession *session, t_lenv *env, char **str, int f)
{
	char	*new_value;
	char	*var;

	new_value = ft_strdup(session, "", 0);
	while (**str && **str != '"' && !(!f && **str == '\''))
	{
		if (**str && **str != '$')
			new_value = ft_joinchar(session, new_value, *((*str)++));
		else if (**str && **str == '$')
		{
			if (*((*str) + 1) && *((*str) + 1) == '?' && (*str)++ && (*str)++)
				new_value = ft_strjoin(session, new_value, get_exit_status(session, env));
			else if (f && *((*str) + 1) && (*((*str) + 1) == '"' || *((*str) + 1) == '\''))
				new_value = ft_joinchar(session, new_value, *((*str)++));
			else if (*((*str) + 1) && *((*str) + 1) != '$' && (*str)++)
			{
				var = get_env(env, var_name_strdup(session, str));
				new_value = ft_strjoin(session, new_value, var);
			}
			else if (**str && **str != '"')
				new_value = ft_joinchar(session, new_value, *((*str)++));
		}
	}
	//puts(*str);
	return (new_value);
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
			//puts(str);
		}
		else if (*str == '"')
		{
			res = ft_joinchar(session, res, *(str++));
			res = ft_strjoin(session, res, var_expansion(session, env, &str, 1));
			res = ft_joinchar(session, res, *(str++));
		}
		else if (*str == '$' && *(str + 1) == '\'')
			str++;
		else if (*str == '$' && !is_identif(*(str + 1)))
			res = ft_joinchar(session, res, *(str++));
		else if (*str)
			res = ft_strjoin(session, res, var_expansion(session, env, &str, 0));
	return (del_from_session(session, tmp), res);
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

static char	*add_var_quotes(t_memsession *s, char *str)
{
	char	*res;

	res = ft_strdup(s, "\"", 0);
	res = ft_strjoin(s, res, str);
	res = ft_joinchar(s, res, '\"');
	del_from_session(s, str);
	return (res);
}

/*
* Expand Vars and whats inside quotes and remove quotes
*/
int	expander(t_memsession *session, t_lenv *env, t_token **cmd)
{
	int		i;
	int		f;

	i = -1;
	f = 0;
	while (cmd && cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN || cmd[i]->type == T_INPUT_FILE
			|| cmd[i]->type == T_OUTPUT_FILE)
		{
			if (cmd[i]->value[0] == '$' && cmd[i]->value[1] && cmd[i]->value[1] != '?')
				f = 1;
			cmd[i]->value = expand_1(session, env, cmd[i]->value);
			cmd[i]->value = expand_2(session, cmd[i]->value);
			if (f)
				cmd[i]->value = add_var_quotes(session, cmd[i]->value);
			//puts(cmd[i]->value);
		}
		if (cmd[i]->type == T_INPUT_FILE || cmd[i]->type == T_OUTPUT_FILE)
			if (ft_countword(cmd[i]->value, SEPERATORS) > 1)
				return (throw_error("ambiguous redirect", 0, 18, 0), -1);
	}
	return (0);
}
