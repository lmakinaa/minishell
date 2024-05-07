/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:45:49 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/07 20:34:25 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*custom_strjoin(t_memsession *session, char *s1, char *s2)
{
	int		i;
	char	*res;

	if (!s1)
	{
		s1 = session_malloc(session, 1 * sizeof(char), 0);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	res = session_malloc(session,
		(ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char), 0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (*s2)
		res[i++] = *(s2++);
	res[i] = '\0';
	del_from_session(session, s1);
	return (res);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (s[i] == c)
		return (&s[i]);
	return (0);
}
