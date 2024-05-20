/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:03:34 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/20 16:06:33 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	**append_arg(t_memsession *session, char **args, char *value, int cmd)
{
	char	**res;
	int		i;
	int		j;

	if (!args)
	{
		res = session_malloc(session, 2 * sizeof(char *), 0);
		res[0] = value;
		res[1] = NULL;
		return (res);
	}
	i = 0;
	while (args[i])
		i++;
	res = session_malloc(session, (i + 2) * sizeof(char *), 0);
	j = -1;
	while (++j < i)
		res[j] = args[j];
	if (cmd)
		res[j++] = value;
	else
		res[j++] = value;
	res[j] = NULL;
	del_from_session(session, args);
	return (res);
}

char	**append_arr(t_memsession *session, char **arr1, char **arr2, int size)
{
	char	**res;
	int		i;
	int		j;

	if (!arr1)
		return (arr2);
	i = 0;
	while (arr1[i])
		i++;
	res = session_malloc(session, (i + size + 1) * sizeof(char *), 0);
	j = -1;
	while (++j < i)
		res[j] = arr1[j];
	while (j < i + size)
		res[j++] = *(arr2++);
	res[j] = NULL;
	del_from_session(session, arr1);
	return (res);
}

int	is_identif(char c)
{
	return (ft_isalpha(c) || c == '?' || c == '_'
		|| (c == '\'' || c == '"'));
}

char	*var_name_strdup(t_memsession *session, char **str)
{
	int		i;
	int		j;
	char	*res;
	char	*s;
	char	*resaddr;

	i = -1;
	s = *str;
	while (s[++i] && ft_isalnum(s[i]))
		;
	res = session_malloc(session, (i + 1) * sizeof(char), 1);
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
