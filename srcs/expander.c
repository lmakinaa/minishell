/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:12:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/21 19:09:30 by ijaija           ###   ########.fr       */
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

//void	var_replace(t_memsession *session, t_token *token, t_lenv *env, char **str_ptr)
//{
	
//}

char	*var_expansion(t_memsession *session, t_lenv *env, char *str)
{
	char	*var;
	char	*new_value;

	new_value = ft_strdup(session, "", 0);
	while (*str)
	{
		if (*str == '\'' && str++)
		{
			new_value = ft_strjoin(session, new_value, z_strdup(session, &str, "'"));
			str++;
		}
		else
		{
			if (*str != '$')
				new_value = ft_charjoin(session, new_value, *str);
			if (*str == '$')
			{
				if (*(str + 1) && *(str + 1) != '$' && str++)
				{
					var = get_env(env, z_strdup(session, &str, "$'\""));
					new_value = ft_strjoin(session, new_value, var);
				}
				else
					new_value = ft_charjoin(session, new_value, *(str++));
			}
			else
				str++;
		}
	}
	return (new_value);
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
			
			printf("%s\n", var_expansion(session, env, cmd[i]->value));
			//printf("%s\n", var_expansion(session, env, cmd[i]->value));
		}
	}
	return (0);
}