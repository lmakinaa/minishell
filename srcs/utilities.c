/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:08:51 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/04 21:09:15 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	what_ops(char *str)
{
	if (!ft_strcmp(str, "||"))
		return (T_OR);
	if (!ft_strcmp(str, "&&"))
		return (T_AND);
	if (!ft_strcmp(str, ">>"))
		return (T_APPEND_REDIRECTOR);
	if (!ft_strcmp(str, "<<"))
		return (T_HERDOC);
	if (!ft_strcmp(str, "<"))
		return (T_INPUT_REDIRECTOR);
	if (!ft_strcmp(str, ">"))
		return (T_OUTPUT_REDIRECTOR);
	if (!ft_strcmp(str, "|"))
		return (T_PIPE);
	return (-1);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	get_token_type(char *str, int is_op)
{
	if (str[0] == '(')
		return (T_PARENTHESIS_COMMAND);
	if (is_op)
		return (what_ops(str));
	if (str[0] == '"' || str[0] == '\'')
		return (T_WORD);
	return (T_UNKNOWN);
}

int	is_redirector(t_token tok)
{
	int	t;

	t = tok.type;
	if (t == T_APPEND_REDIRECTOR || t == T_HERDOC
		|| t == T_INPUT_REDIRECTOR || t == T_OUTPUT_REDIRECTOR)
		return (1);
	return (0);
}
