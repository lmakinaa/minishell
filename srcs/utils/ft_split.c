/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:03:09 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 14:49:41 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	sep_check(char c, char *seps)
{
	int	i;

	i = -1;
	while (seps[++i])
		if (seps[i] == c)
			return (1);
	return (0);
}

static int	ft_count_words(char *str, char *seps)
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

static char	*custom_strdup(t_memsession *session, char *s, char *seps)
{
	int		i;
	int		j;
	char	*res;
	char	*resaddr;

	i = 0;
	j = 0;
	while (s[i] && !sep_check(s[i], seps))
		i++;
	res = session_malloc(session, (i + 1) * sizeof(char));
	resaddr = res;
	while (j < i && !sep_check(s[j], seps))
	{
		*res = s[j];
		res++;
		j++;
	}
	*res = '\0';
	return (resaddr);
}

void	spliting_process(t_memsession *session,
	t_splitdata *result, char *str, char *seps)
{
	int	i;

	i = -1;
	while (*str && ++i < result->word_count)
	{
		if (!sep_check(*str, seps))
		{
			result->words[i] = custom_strdup(session, str, seps);
			while (*str && !sep_check(*str, seps))
				str++;
		}
		while (*str && sep_check(*str, seps))
			str++;
	}
	result->words[i] = NULL;
}

t_splitdata	*ft_split(t_memsession *session, char *str, char *seps)
{
	t_splitdata	*result;

	if (!str || !seps)
		return (NULL);
	result = session_malloc(session, sizeof(t_splitdata));
	result->word_count = ft_count_words(str, seps);
	result->words = session_malloc(session,
			(result->word_count + 1) * sizeof(char *));
	spliting_process(session, result, str, seps);
	return (result);
}
