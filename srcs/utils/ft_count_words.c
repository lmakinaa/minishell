/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:17:46 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/04 00:40:20 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	is_ops(char c)
{
	if (c == '&' || c == '|' || c == '>'
		|| c == '<' || c == '"' || c == '\'' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	sep_check(char c, char *seps)
{
	int	i;

	i = -1;
	while (seps[++i])
		if (seps[i] == c || is_ops(c))
			return (1);
	return (0);
}

void	skip_inside_parenthesis(char **s)
{
	int	open;

	open = 1;
	while (**s && open != 0)
	{
		while (++(*s) && **s && **s != ')')
		{
			if (**s == '(')
				open++;
		}
		open--;
	}
	(*s)++;
}

int	new_is_ops(char *c)
{
	if ((*c == '&' && *(c + 1) == '&') || *c == '|' || *c == '>'
		|| *c == '<' || *c == '"' || *c == '\'' || *c == '(' || *c == ')')
		return (1);
	return (0);
}

int	new_sep_check(char *c, char *seps)
{
	int	i;

	i = -1;
	while (seps[++i])
		if (seps[i] == *c || new_is_ops(c))
			return (1);
	return (0);
}

void	count_operators(char **s, int *res)
{
	char	*str;
	char	tmp;

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
	else if (*str == '\'' || *str == '"')
	{
		(*res)++;
		tmp = *str;
		while (++(*s) && **s && **s != tmp)
			;
		(*s)++;
	}
	else if (*str == '(' || *str == ')')
		return ((*res)++, skip_inside_parenthesis(s));
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
			while (*str && !new_sep_check(str, 	seps))
				str++;
		}
		if (*str && !new_is_ops(str))
			str++;
	}
	printf("%d\n", res);
	return (res);
}
