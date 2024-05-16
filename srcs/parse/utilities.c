/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:08:51 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/16 16:32:01 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	what_ops(char *str)
{
	if (!ft_strcmp(1, str, "||"))
		return (T_OR);
	if (!ft_strcmp(1, str, "&&"))
		return (T_AND);
	if (!ft_strcmp(1, str, ">>"))
		return (T_APPEND_REDIR);
	if (!ft_strcmp(1, str, "<<"))
		return (T_HERDOC);
	if (!ft_strcmp(1, str, "<"))
		return (T_INPUT_REDIRECTOR);
	if (!ft_strcmp(1, str, ">"))
		return (T_OUT_REDIR);
	if (!ft_strcmp(1, str, "|"))
		return (T_PIPE);
	return (-1);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(0, str, "echo") || !ft_strcmp(0, str, "cd")
		|| !ft_strcmp(0, str, "pwd") || !ft_strcmp(0, str, "export"))
		return (1);
	if (!ft_strcmp(0, str, "unset") || !ft_strcmp(0, str, "env")
		|| !ft_strcmp(0, str, "exit"))
		return (1);
	return (0);
}

int	get_token_type(char *str)
{
	if (str[0] == '(')
		return (T_PARENTHESIS_COMMAND);
	if (new_is_ops(str))
		return (what_ops(str));
	return (T_UNKNOWN);
}

int	is_redirector(t_token tok)
{
	int	t;

	t = tok.type;
	if (t == T_APPEND_REDIR || t == T_HERDOC
		|| t == T_INPUT_REDIRECTOR || t == T_OUT_REDIR)
		return (1);
	return (0);
}

int	get_precedence(t_token *token)
{
	if (token->type == T_AND)
		return (0);
	else if (token->type == T_OR)
		return (0);
	return (1);
}
