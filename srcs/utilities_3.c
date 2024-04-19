/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:52:57 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 18:05:25 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	are_parenthesis_closed(char *s)
{
	int	i;
	int	open;
	int	close;

	i = -1;
	open = 0;
	close = 0;
	while (s[++i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
			close++;
		if (close > open)
			return (syntax_error("related to parentheses", 22), 1);
	}
	if (close != open)
		return (syntax_error("related to parentheses", 22), 1);
	return (0);
}

int	are_quotes_closed(char *s)
{
	int		i;
	int		open;
	char	tmp;

	i = -1;
	open = 0;
	while (s[++i])
	{
		open = 0;
		if (s[i] == '\'' || s[i] == '"')
		{
			open = 1;
			tmp = s[i++];
			while (s[i] && s[i] != tmp)
				i++;
			if (!s[i])
				return (syntax_error("related to quotes", 17), 1);
		}
	}
	return (0);
}
