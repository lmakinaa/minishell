/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:12:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/06/08 18:59:45 by ijaija           ###   ########.fr       */
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
				new_value = ft_strjoin(session, new_value,
						get_exit_status(session, env));
			else if (f && *((*str) + 1)
				&& (*((*str) + 1) == '"' || *((*str) + 1) == '\''))
				new_value = ft_joinchar(session, new_value, *((*str)++));
			else if (*((*str) + 1) && *((*str) + 1) != '$' && (*str)++)
				(1) && (var = get_env(env, var_name_strdup(session, str)),
					new_value = ft_strjoin(session, new_value, var));
			else if (**str && **str != '"')
				new_value = ft_joinchar(session, new_value, *((*str)++));
		}
	}
	return (new_value);
}

char	*expand_1(t_memsession *session, t_lenv *env, char *str)
{
	char	*res;
	char	*tmp;

	tmp = str;
	res = ft_strdup(session, "", 0);
	while (*str)
	{
		if (*str == '\'')
			(1) && (res = ft_joinchar(session, res, *(str++)),
				res = ft_strjoin(session, res, z_strdup(session, &str, "'")),
				res = ft_joinchar(session, res, *(str++)));
		else if (*str == '"')
			(1) && (res = ft_joinchar(session, res, *(str++)),
				res = ft_strjoin(session, res,
				var_expansion(session, env, &str, 1)),
				res = ft_joinchar(session, res, *(str++)));
		else if (*str == '$' && *(str + 1) == '\'')
			str++;
		else if (*str == '$' && !is_identif(*(str + 1)))
			res = ft_joinchar(session, res, *(str++));
		else if (*str)
			res = ft_strjoin(session, res,
					var_expansion(session, env, &str, 0));
	}
	return (res);
}

char	*expand_2(t_memsession *session, char *str)
{
	char	*res;
	char	*s;

	res = ft_strdup(session, "", 0);
	while (*str)
	{
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
	}
	s = no_quotes(session, res, 1);
	if (ft_strchr(s, 127))
	{
		s = expand_wildcard(session, s);
		if (s)
			return (s);
	}
	return (res);
}

/*
* Expand Vars and whats inside quotes and remove quotes
*/
int	expander(t_memsession *session, t_lenv *env, t_token **cmd)
{
	int		i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN || cmd[i]->type == T_INPUT_FILE
			|| cmd[i]->type == T_OUTPUT_FILE)
		{
			if ((cmd[i]->type == T_INPUT_FILE || cmd[i]->type == T_OUTPUT_FILE))
				if (ft_countword(expand_1(session, env, cmd[i]->value),
						SEPERATORS, 0) != 1)
					return (throw_error("ambiguous redirect", 0, 18, 0), -1);
			if (cmd[i]->value[0] == '$' && cmd[i]->value[1]
				&& cmd[i]->value[1] != '?')
				cmd[i]->type = T_VAR;
			cmd[i]->value = expand_1(session, env, cmd[i]->value);
			cmd[i]->value = expand_2(session, cmd[i]->value);
		}
	}
	return (0);
}

t_command	*expand_n_generate_cmd(t_memsession *session, t_lenv *env,
	t_token **node)
{
	t_command	*cmd;

	if (tokenize_part2(node) == -1 || expander(session, env, node) == -1)
	{
		env->exit_status = 1;
		return (NULL);
	}
	cmd = parse_cmd(session, env, node, -1);
	return (cmd);
}
