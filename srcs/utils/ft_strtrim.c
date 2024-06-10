/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:20:39 by ijaija            #+#    #+#             */
/*   Updated: 2024/06/10 16:24:49 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static char	*ft_substr(t_memsession *sess, char *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(sess, "", 0));
	if (len >= slen)
		len = slen;
	if (len >= (slen - start))
		len = slen - start;
	res = session_malloc(sess, (len + 1) * sizeof(char), 0);
	while (i < len)
	{
		res[i] = s[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	ft_isin(const char *s, char c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (1);
	return (0);
}

char	*ft_strtrim(t_memsession *s, char *s1, char *set)
{
	size_t	fchar;
	size_t	lchar;
	char	*res;

	if (!s1)
		return (NULL);
	if (!set)
		return (s1);
	if (s1[0] == '\0')
		return (s1);
	fchar = 0;
	lchar = ft_strlen(s1);
	while (ft_isin(set, s1[fchar]))
		fchar++;
	if (fchar == lchar)
		return (ft_strdup(s, "", 0));
	while (ft_isin(set, s1[lchar - 1]))
		lchar--;
	res = ft_substr(s, s1, fchar, lchar - fchar);
	return (res);
}
