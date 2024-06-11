/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:13:28 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/02 22:19:11 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/*
* Returns -1 on error (if one of them is Null)
* Returns 0 if they are similar and a positive number if not
*/
int	ft_strncmp(char *str, char *compared_to, int n)
{
	int	i;

	if (!str || !compared_to)
		return (-1);
	i = 0;
	while (str[i] && compared_to[i] && str[i] == compared_to[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (1);
}
