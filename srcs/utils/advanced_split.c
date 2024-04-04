/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:03:09 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/04 02:00:53 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static char	*custom_strdup(t_memsession *session, char *s, char *seps)
{
	int		i;
	int		j;
	char	*res;
	char	*resaddr;

	i = 0;
	j = 0;
	while (s[i] && !new_sep_check(&s[i], seps))
		i++;
	res = session_malloc(session, (i + 1) * sizeof(char), 0);
	resaddr = res;
	while (j < i && !new_sep_check(&s[j], seps))
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
	res = session_malloc(session, (i + 1) * sizeof(char), 0);
	resaddr = res;
	*(res++) = sep;
	j = 0;
	while (++j < i && s[j] != sep)
		*(res++) = s[j];
	if (s[j] == sep)
		*(res++) = s[j];
	*res = '\0';
	*str += i;
	return (resaddr);
}

void	parenthesis_strdup(t_memsession *session, char **s, char **r)
{
	int		open;
	char	*res;
	char	*tmp;

	tmp = *s;
	*r = session_malloc(session,
		(skip_inside_parenthesis(&tmp) + 1) * sizeof(char), 0);
	res = *r;
	open = 1;
	*(res++) = **s;
	while (**s && open != 0)
	{
		while (++(*s) && **s && **s != ')')
		{
			if (**s == '(')
				open++;
			*(res++) = **s;
		}
		open--;
	}
	*(res++) = *(*s++);
	*res = '\0';
}

char	*operators_strdup(t_memsession *session, char **str)
{
	char	*res;

	res = NULL;
	if (!ft_strncmp(*str, "&&", 2) || !ft_strncmp(*str, "||", 2)
		|| !ft_strncmp(*str, ">>", 2) || !ft_strncmp(*str, "<<", 2))
	{
		res = session_malloc(session, 3 * sizeof(char), 0);
		ft_strncpy(res, *str, 2);
		(*str) += 2;
	}
	else if (**str == '<' || **str == '>' || **str == '|')
	{
		res = session_malloc(session, 2 * sizeof(char), 0);
		ft_strncpy(res, *str, 1);
		(*str)++;
	}
	else if (**str == '\'' || **str == '"')
		res = quotes_strdup(session, str, **str);
	else if (**str == '(')
		parenthesis_strdup(session, str, &res);
	return (res);
}

void	spliting_process(t_memsession *session,
	t_splitdata *result, char *str, char *seps)
{
	int		i;

	i = 0;
	while (*str && i < result->word_count)
	{
		if (new_is_ops(str))
			result->words[i++] = operators_strdup(session, &str);
		if (*str && !new_sep_check(str, seps))
		{
			result->words[i++] = custom_strdup(session, str, seps);
			while (*str && !new_sep_check(str, seps))
				str++;
		}
		if (*str && !new_is_ops(str))
			str++;
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
	result = session_malloc(session, sizeof(t_splitdata), 0);
	tmp = result;
	result->word_count = ft_count_words(str, seps);
	result->words = session_malloc(session,
			(result->word_count + 1) * sizeof(char *), 0);
	spliting_process(session, result, str, seps);
	return (tmp);
}
