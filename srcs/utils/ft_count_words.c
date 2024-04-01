/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:17:46 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/01 18:46:48 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	ft_count_words(char *str, char *seps)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i])
	{
		if (!sep_check(str[i], seps))
		{
			res++;
			while (str[i] && !sep_check(str[i], seps))
				i++;
		}
		i++;
	}
	return (res);
}
