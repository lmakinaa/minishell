/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:15:11 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/24 17:01:31 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	pattern_check_2(char *str, char *pattern, int s_len, int *j)
{
	int	i;
	int	str_index;
	int	pat_index;

	str_index = -1;
	pat_index = -1;
	i = 0;
	while (i < s_len)
		if (str[i] == pattern[*j] && ++i && ++(*j))
			;
		else if (pattern[*j] == 127)
		{
			str_index = i;
			pat_index = *j;
			(*j)++;
		}
		else if (pat_index != -1)
		{
			i = str_index + 1;
			(*j) = pat_index + 1;
			str_index++;
		}
		else
			return (0);
	return (1);
}

int	pattern_check(char *str, char *pattern)
{
	int	j;
	int	p_len;

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
		if (pattern_check(str, entry->d_name))
		{
			res = ft_strjoin(session, res, entry->name);
			res = ft_joinchar(session, res, ' ');
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (res);
}

char	*expand_2(t_memsession *session, char *str)
{
	char	*res;
	char	tmp[2];

	res = ft_strdup(session, "", 0);
	tmp[1] = '\0';
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && str++)
		{
			tmp[0] = *str;
			res = ft_strjoin(session, res, z_strdup(session, &str, tmp));
			str++;
		}
		else if (*str == '*' && str++)
			res = ft_joinchar(session, res, 127);
		else
			res = ft_joinchar(session, res, *(str++));
	}
	if (ft_strchr(res, 127))
		return (expand_wildcard(session, res));
	return (res);
}
