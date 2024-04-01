/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:03:09 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/01 21:01:26 by ijaija           ###   ########.fr       */
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

static char	*quotes_strdup(t_memsession *session, char **str, char sep)
{
	int		i;
	int		j;
	char	*s;
	char	*res;
	char	*resaddr;

	s = *str;
	i = 1;
	while (s[i] && s[i] != sep)
		i++;
	if (s[i] == sep)
		i++;
	res = session_malloc(session, (i + 1) * sizeof(char));
	resaddr = res;
	*(res++) = sep;
	j = 1;
	while (j < i && s[j] != sep)
	{
		*res = s[j];
		res++;
		j++;
	}
	if (s[j] == sep)
		*(res++) = s[j];
	*res = '\0';
	*str += i;
	return (resaddr);
}

void	spliting_process(t_memsession *session,
	t_splitdata *result, char *str, char *seps)
{
	int		i;

	i = 0;
	while (*str && i < result->word_count)
	{
		if (*str == '\'' || *str == '"')
			result->words[i] = quotes_strdup(session, &str, *str);
		else if (!sep_check(*str, seps))
		{
			result->words[i] = custom_strdup(session, str, seps);
			while (*str && !sep_check(*str, seps))
				str++;
		}
		while (*str && sep_check(*str, seps))
			str++;
		i++;
	}
	result->words[i] = NULL;
}

/*
* It returns a data structure that have as members :
* 	- word_count : the number of slitted strings
*	- words : the array of strings that has the splitted strings
*/
t_splitdata	*advanced_split(t_memsession *session, char *str, char *seps)
{
	t_splitdata	*result;
	t_splitdata	*tmp;

	if (!str || !seps)
		return (NULL);
	result = session_malloc(session, sizeof(t_splitdata));
	tmp = result;
	result->word_count = ft_count_words(str, seps);
	result->words = session_malloc(session,
			(result->word_count + 1) * sizeof(char *));
	spliting_process(session, result, str, seps);
	return (tmp);
}
