/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:17:46 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/01 20:39:29 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	ft_count_words(char *str, char *seps)
{
	int		res;
	int		i;
	char	tmp;

	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			res++;
			tmp = str[i];
			while (str[++i] && str[i] != tmp)
				;
		}
		else if (!sep_check(str[i], seps))
		{
			res++;
			while (str[i] && !sep_check(str[i], seps))
				i++;
		}
		if (str[i])
			i++;
	}
	return (res);
}
