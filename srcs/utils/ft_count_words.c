/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:17:46 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/02 00:12:15 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	sep_check(char c, char *seps)
{
	int	i;

	i = -1;
	while (seps[++i])
		if (seps[i] == c)
			return (1);
	return (0);
}

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
