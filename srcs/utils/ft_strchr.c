/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:45:49 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 17:23:39 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	character;
	char	*str;

	i = 0;
	str = (char *) s;
	character = (char) c;
	while (str[i])
	{
		if (str[i] == character)
			return (&str[i]);
		i++;
	}
	if (str[i] == character)
		return (&str[i]);
	return (NULL);
}