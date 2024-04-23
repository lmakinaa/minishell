/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:12:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/23 17:48:31 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*var_expansion(t_memsession *session, t_lenv *env, char **str)
{
	char	*new_value;
	char	*var;

	new_value = ft_strdup(session, "", 0);
	while (**str && **str != '"')
	{
		if (**str && **str != '$')
		{
			new_value = ft_joinchar(session, new_value, *((*str)++));
		}
		else if (**str && **str == '$')
		{
			if (*((*str) + 1) && *((*str) + 1) != '$' && (*str)++)
			{
				var = get_env(env, z_strdup(session, str, "$\"'"));
				new_value = ft_strjoin(session, new_value, var);
			}
			else if (**str && **str != '"')
				new_value = ft_joinchar(session, new_value, *((*str)++));
		}
	}
	return (new_value);
}

char	*expand_word(t_memsession *session, t_lenv *env, char *str)
{
	char	*res;
	char	*tmp;

	tmp = str;
	res = ft_strdup(session, "", 0);
	while (*str)
	{
		if (*str == '\'' && str++)
			res = ft_strjoin(session, res, z_strdup(session, &str, "'"));
		else if (*str == '"' && str++)
			res = ft_strjoin(session, res, var_expansion(session, env, &str));
		else if (*str)
			res = ft_strjoin(session, res, var_expansion(session, env, &str));
	}
	del_from_session(session, tmp);
	return (res);
}

//char	*expand_wildcard(t_memsession *session, char *str)
//{
//	char	*res;
//	char	*tmp;

//	tmp = str;
//	res = ft_strdup(session, "", 0);
//	while (*str)
//	{
//		if (*str == '*');
//	}
//	del_from_session(session, tmp);
//	return (res);
//}

/*
* Expand Vars and whats inside quotes and remove quotes
*/
int	expander(t_memsession *session, t_lenv *env, t_token **cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN)
		{
			cmd[i]->value = expand_word(session, env, cmd[i]->value);
			//cmd[i]->value = expand_wildcard(session, cmd[i]->value);
		}
	}
	return (0);
}
