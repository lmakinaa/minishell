/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:09:35 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/17 14:24:30 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	ft_countword(char *str, char *seps)
{
	char	tmp;
	int		count;

	count = 0;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!is_sep(*str, seps) && ++count)
		{
			while (*str && !is_sep(*str, seps))
				if (*str == '"' || *str == '\'')
				{
					tmp = *(str++);
					while (*(str) && *str != tmp)
						str++;
					(*str) && (str++);
				}
				else
					str++;
		}
		if (*str)
			str++;
	}
	return (count);
}

char	*split_strdup(t_memsession *session, char *s, char *seps)
{
	int		i;
	int		j;
	char	*res;
	char	*resaddr;

	i = 0;
	j = 0;
	while (s[i] && !is_sep(s[i], seps))
		i++;
	res = session_malloc(session, (i + 1) * sizeof(char), 0);
	resaddr = res;
	while (j < i && !is_sep(s[j], seps))
	{
		*res = s[j];
		res++;
		j++;
	}
	*res = '\0';
	return (resaddr);
}

static	void	split_process(t_memsession *session, t_splitdata *data, char *s, char *seps)
{
	int		i;
	char	tmp;
	char	**res;

	res = data->words;
	i = 0;
	while (i < data->word_count && *s)
	{
		if (!is_sep(*s, seps))
		{
			res[i++] = custom_strdup(session, s, seps);
			while (*s && !is_sep(*s, seps))
				if (*s == '"' || *s == '\'')
				{
					tmp = *s;
					while (*(++s) && *s != tmp)
						;
				}
				else
					s++;
		}
		if (*s)
			s++;
	}
	res[i] = NULL;
}

t_splitdata	*ft_split(t_memsession *session, char *s, char *seps)
{
	int			size;
	t_splitdata	*data;

	if (!s)
		return (NULL);
	size = ft_countword(s, seps);
	data = session_malloc(session, sizeof(t_splitdata), 0);
	data->word_count = size;
	data->words = session_malloc(session, (size + 1) * sizeof(char *), 0);
	split_process(session, data, s, seps);
	return (data);
}
