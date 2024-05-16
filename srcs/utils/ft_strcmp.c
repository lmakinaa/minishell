/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:41:11 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/16 10:47:29 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	compare_cases(char c1, char c2)
{
	char	rev_case;

	if (c2 >= 'a' && c2 <= 'z')
		rev_case = c2 - 32;
	else if (c2 >= 'A' && c2 <= 'Z')
		rev_case = c2 + 32;
	else
		rev_case = c2;
	if (c1 == c2 || c1 == rev_case)
		return (0);
	return (1);
}

/*
* Returns -1 on error (if one of them is Null)
* Returns 0 if they are similar and a positive number if not
*/
int	ft_strcmp(int case_sensitive, char *str, char *compared_to)
{
	int	i;

	if (!str || !compared_to)
		return (-1);
	i = 0;
	if (!case_sensitive)
		while (str[i] && compared_to[i] && !compare_cases(str[i], compared_to[i]))
			i++;
	else
		while (str[i] && compared_to[i] && str[i] == compared_to[i])
			i++;
	return (str[i] - compared_to[i]);
}
