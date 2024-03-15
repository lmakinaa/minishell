/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:16:54 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/15 14:49:47 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

/*
* It don't check for wildcards, you should check them later
*/
int	get_token_type(char *str, int order)
{
	if (order == 0 && !is_builtin(str))
		return (T_EXECUTABLE);
	if (order == 0 && is_builtin(str))
		return (T_BUILTIN);
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		return (T_REDIRECTORS);
	if (!ft_strcmp(str, "'") || !ft_strcmp(str, "\""))
		return (T_QUOTES);
	if (!ft_strcmp(str, "|"))
		return (T_PIPE);
	if (!ft_strcmp(str, "||"))
		return (T_OR);
	if (!ft_strcmp(str, "&&"))
		return (T_AND);
	if (!ft_strcmp(str, "$?"))
		return (T_AUTOMATIC_VAR);
	if (str[0] == '$')
		return (T_VAR);
	if (str[0] == '-')
		return (T_FLAG);
	return (T_ARG);
}
