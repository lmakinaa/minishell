/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:17:46 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 18:07:50 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	skip_inside_parenthesis(char **s)
{
	int	open;
	int	len;

	open = 1;
	len = 1;
	while (**s && open != 0)
	{
		while (++(*s) && **s && **s != ')')
		{
			if (**s == '(')
				open++;
			len++;
		}
		open--;
	}
	(*s)++;
	return (len + 1);
}

int	new_is_ops(char *c)
{
	if ((*c == '&' && *(c + 1) == '&') || *c == '|' || *c == '>'
		|| *c == '<' || *c == '(' || *c == ')')
		return (1);
	return (0);
}

void	count_operators(char **s, int *res)
{
	char	*str;
	//char	tmp;

	str = *s;
	if (!ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2)
		|| !ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
	{
		(*res)++;
		(*s) += 2;
	}
	else if (*str == '<' || *str == '>' || *str == '|')
	{
		(*res)++;
		(*s)++;
	}
	//else if (*str == '\'' || *str == '"')
	//{
	//	(*res)++;
	//	tmp = *str;
	//	while (++(*s) && **s && **s != tmp)
	//		;
	//	(*s)++;
	//}
	else if (*str == '(' || *str == ')')
		return ((*res)++, skip_inside_parenthesis(s), void_return());
}

int	ft_count_words(char *str, char *seps)
{
	int		res;

	res = 0;
	while (*str)
	{
		count_operators(&str, &res);
		if (*str && !new_sep_check(str, seps))
		{
			res++;
			while (*str && !new_sep_check(str, seps))
				str++;
		}
		if (*str && !new_is_ops(str))
			str++;
	}
	return (res);
}
