/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shave_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:30:21 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/18 18:43:34 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/*
* t9ra3 string mn l a9was
*/
char	*shave_parenthesis(t_memsession *session, char *s)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s) - 1;
	res = session_malloc(session, len * sizeof(char), 0);
	i = 0;
	j = 0;
	while (s[++i] && i < len)
	{
		res[j] = s[i];
		j++;
	}
	res[j] = '\0';
	return (res);
}

t_tnode	*nested_tree(t_memsession *session, t_token ***tokens)
{
	t_token	**nested_tokens;
	char	*nested_command;
	t_tnode	*root;

	nested_command = shave_parenthesis(session, (**tokens)->value);
	if (!nested_command[0])
		return (s_s(session->envs, 1),
			throw_error(SYNTAX_ERR, ")", SYNTAX_ERR_LEN, 1), NULL);
	nested_tokens = advanced_split(session, nested_command, SEPERATORS);
	root = build_tree(session, &nested_tokens, 0);
	(*tokens)++;
	return (root);
}
