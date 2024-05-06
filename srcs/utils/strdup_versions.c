/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_versions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:12:22 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/06 17:57:22 by ijaija           ###   ########.fr       */
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
	else if (**str == '(')
		parenthesis_strdup(session, str, &res);
	return (res);
}

static	int	custom_strlen(char *s, char *seps)
{
	int		i;
	char	tmp;
	
	i = 0;
	while (s[i] && !new_sep_check(&s[i], seps))
		if (s[i] == '"' || s[i] == '\'')
		{
			tmp = s[i++];
			while (s[i] && s[i] != tmp)
				i++;
			i++;
		}
		else
			i++;
	return (i);
}

char	*custom_strdup(t_memsession *session, char *s, char *seps)
{
	int		i;
	int		j;
	char	*res;
	char	*resaddr;

	i = custom_strlen(s, seps);
	res = session_malloc(session, (i + 1) * sizeof(char), 0);
	resaddr = res;
	j = 0;
	while (j < i)
	{
		*res = s[j];
		res++;
		j++;
	}
	*res = '\0';
	return (resaddr);
}

char	*z_strdup(t_memsession *session, char **str, char *seps)
{
	int		i;
	int		j;
	char	*res;
	char	*s;
	char	*resaddr;
	
	i = -1;
	s = *str;
	while (s[++i] && !is_sep(s[i], seps))
		;
	res = session_malloc(session, (i + 1) * sizeof(char), 1);
	resaddr = res;
	j = 0;
	while (j < i)
	{
		*res = s[j];
		res++;
		j++;
	}
	*res = '\0';
	(*str) += j;
	return (resaddr);
}

char	*var_name_strdup(t_memsession *session, char **str)
{
	int		i;
	int		j;
	char	*res;
	char	*s;
	char	*resaddr;
	
	i = -1;
	s = *str;
	while (s[++i] && ft_isalnum(s[i]))
		;
	res = session_malloc(session, (i + 1) * sizeof(char), 1);
	resaddr = res;
	j = 0;
	while (j < i)
	{
		*res = s[j];
		res++;
		j++;
	}
	*res = '\0';
	(*str) += j;
	return (resaddr);
}
