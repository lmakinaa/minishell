/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:30:46 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/17 14:41:19 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*ft_strdup(t_memsession *session, char *s1, size_t len)
{
	char	*res;
	size_t	i;

	if (!s1)
		return (NULL);
	i = 0;
	res = session_malloc(session, (len + 2) * sizeof(char), 0);
	while (s1[i] && i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = s1[i];
	if (res[i])
		(1) && (i++, res[i] = '\0');
	return (res);
}
