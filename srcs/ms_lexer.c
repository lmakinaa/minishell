/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:04:32 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/04 20:23:39 by ijaija           ###   ########.fr       */
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

/*
* In this part we identifie the operators specefically 
*/
t_token	*tokenize_part_1(t_memsession *session, t_splitdata *splited_cmd)
{
	int		i;
	t_token	*tokens;

	tokens = session_malloc(session,
		splited_cmd->word_count * sizeof(t_token), 0);
	i = -1;
	while (++i < splited_cmd->word_count)
	{
		tokens[i].tokens_nbr = splited_cmd->word_count;
		tokens[i].order = i;
		tokens[i].value = splited_cmd->words[i];
		tokens[i].is_operator = new_is_ops(splited_cmd->words[i]);
		tokens[i].len = ft_strlen(splited_cmd->words[i]);
		tokens[i].type = get_token_type(splited_cmd->words[i], tokens[i].is_operator);
		tokens[i].command = 1;
	}
	return (tokens);
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

void	tokenize_part_2(t_token *res)
{
	int	i;

	i = -1;
	while (++i < res[0].tokens_nbr)
		if (res[i].is_operator && !is_redirector(res[i])
			&& res[i].type != T_PARENTHESIS_COMMAND)
			res[i].command = 0;
}

t_token	*ms_lexer(t_memsession *session, char *command)
{
	t_token		*res;
	t_splitdata	*splited_cmd;

	splited_cmd = advanced_split(session, command, SEPERATORS);
	if (!splited_cmd->word_count)
		return (NULL);
	res = tokenize_part_1(session, splited_cmd);
	tokenize_part_2(res);
	return (res);
}
