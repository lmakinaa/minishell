/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 23:40:45 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/01 23:48:43 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/utils.h"

static int	ft_isin(const char *s, char c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
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
