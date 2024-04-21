/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:28:10 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/21 21:44:31 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*ft_strjoin(t_memsession *session, char *s1, char *s2)
{
	size_t	size;
	char	*res;
	size_t	i;
	size_t	j;

	if (!s2)
		return (s1);
	size = ft_strlen(s1) + ft_strlen(s2);
	res = session_malloc(session, (size + 1) * sizeof(char), 0);
	i = -1;
	while (++i < size && s1[i])
		res[i] = s1[i];
	j = 0;
	while (i + j < size && *s2)
	{
		if (*s2 != '"')
		{
			res[i + j] = *s2;
			j++;
		}
		s2++;
	}
	res[i + j] = '\0';
	del_from_session(session, s1);
	return (res);
}

char	*ft_joinchar(t_memsession *session, char *s1, char c)
{
	size_t	size;
	char	*res;
	size_t	i;
	size_t	j;

	if (c == '"')
		return (s1);
	size = ft_strlen(s1) + 1;
	res = session_malloc(session, (size + 1) * sizeof(char), 0);
	i = 0;
	j = 0;
	while (i < size && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	del_from_session(session, s1);
	return (res);
}
