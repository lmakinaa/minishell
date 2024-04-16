/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:03:09 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/16 15:10:12 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
