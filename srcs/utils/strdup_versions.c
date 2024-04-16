/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_versions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:12:22 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/16 15:14:27 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
		*(res++) = **s;
		open--;
	}
	*res = '\0';
	(*s)++;
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

char	*quotes_strdup(t_memsession *session, char **str, char sep)
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

char	*custom_strdup(t_memsession *session, char *s, char *seps)
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
