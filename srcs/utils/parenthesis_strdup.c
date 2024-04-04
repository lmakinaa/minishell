/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_strdup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:30:21 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/04 01:03:45 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/utils.h"

int	check_if_parenthesis_closed(char *s)
{
	int	i;
	int	open;
	int	close;

	i = 0;
	open = 0;
	close = 0;
	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
			close++;
		i++;
	}
	if (close != open)
		return (1);
	return (0);
}

char	*parenthesis_strdup(t_memsession *session, char **str, char sep)
{
	int		i;
	int		j;
	char	*s;
	char	*res;
	char	*resaddr;

	
	s = *str;
	if (check_if_parenthesis_closed(s))
		exit_on_error("Syntax error: related to paranthesis", 36);
	i = 1;
	while (s[i] && s[i] != sep)
		i++;
	if (s[i] == sep)
		i++;
	res = session_malloc(session, (i + 1) * sizeof(char));
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