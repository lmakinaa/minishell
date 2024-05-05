/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:41:11 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/05 17:54:34 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/*
* Returns -1 on error (if one of them is Null)
* Returns 0 if they are similar and a positive number if not
*/
int	ft_strcmp(char *str, char *compared_to)
{
	int	i;

	if (!str || !compared_to)
		return (-1);
	i = 0;
	while (str[i] && compared_to[i] && str[i] == compared_to[i])
		i++;
	return (str[i] - compared_to[i]);
}
