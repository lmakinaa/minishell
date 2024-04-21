/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:30:46 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/21 14:41:17 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*ft_strdup(t_memsession *session, char *s1, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	res = session_malloc(session, (len + 1) * sizeof(char), 0);
	while (s1[i] && i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = s1[i];
	return (res);
}
