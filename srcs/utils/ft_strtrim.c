/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:40:45 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 17:23:39 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len >= slen)
		len = slen;
	if (len >= (slen - start))
		len = slen - start;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = s[start];
		start++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(char *s1)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = s1[i];
	return (res);
}

static int	ft_isin(char *s, char c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (1);
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	fchar;
	size_t	lchar;
	char	*res;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	if (s1[0] == '\0')
		return (ft_strdup(""));
	fchar = 0;
	lchar = ft_strlen(s1);
	while (ft_isin(set, s1[fchar]))
		fchar++;
	if (fchar == lchar)
		return (ft_strdup(""));
	while (ft_isin(set, s1[lchar - 1]))
		lchar--;
	res = ft_substr(s1, fchar, lchar - fchar);
	return (res);
}
