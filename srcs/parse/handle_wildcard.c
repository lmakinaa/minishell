/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:15:11 by ijaija            #+#    #+#             */
/*   Updated: 2024/06/10 16:15:28 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	pattern_check_2(char *str, char *pattern, int s_len, int *j)
{
	int	i;
	int	str_index;
	int	pat_index;

	str_index = -1;
	pat_index = -1;
	i = 0;
	while (i < s_len)
	{
		if (str[i] == pattern[*j] && ++i && ++(*j))
			;
		else if (pattern[*j] == 127)
			(1) && (str_index = i, pat_index = *j, (*j)++);
		else if (pat_index != -1)
		{
			i = str_index + 1;
			(*j) = pat_index + 1;
			str_index++;
		}
		else
			return (0);
	}
	return (1);
}

int	pattern_check(char *str, char *pattern)
{
	int	j;
	int	p_len;

	if (str[0] == '.' && pattern[0] != '.')
		return (0);
	j = 0;
	p_len = ft_strlen(pattern);
	if (!pattern_check_2(str, pattern, ft_strlen(str), &j))
		return (0);
	while (j < p_len && pattern[j] == 127 && ++j)
		;
	if (j == p_len)
		return (1);
	return (0);
}

char	*expand_wildcard(t_memsession *session, char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*res;

	dir = opendir(".");
	if (!dir)
		return (exit_on_error("opendir failed\n", 15), NULL);
	res = ft_strdup(session, "", 0);
	entry = readdir(dir);
	while (entry)
	{
		if (pattern_check(entry->d_name, str))
		{
			res = ft_strjoin(session, res, entry->d_name);
			res = ft_joinchar(session, res, ' ');
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (!res[0])
		return (NULL);
	return (res);
}

char	*no_quotes(t_memsession *session, char *str, int flag)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_strdup(session, "", 0);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (*str && *str == '\'' && str++)
				res = ft_strjoin(session, res, z_strdup(session, &str, "'"));
			else if (*str && *str == '"' && str++)
				res = ft_strjoin(session, res, z_strdup(session, &str, "\""));
			if (*str)
				str++;
		}
		else if (*str == '*' && flag && str++)
			res = ft_joinchar(session, res, 127);
		else
			res = ft_joinchar(session, res, *(str++));
	}
	return (res);
}
