/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:12:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/16 15:45:36 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = -1;
	while (++i < n && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (n);
}
