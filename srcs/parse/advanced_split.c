/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:03:09 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/20 15:59:05 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	check_syntax(t_token *tok, int t, t_token *next, int order)
{
	if (t == T_AND || t == T_OR || t == T_PIPE)
	{
		if (!order || !next || (next->type != T_PARENTHESIS_COMMAND
				&& next->type != T_UNKNOWN && !is_redirector(*next)))
			return (throw_error(SYNTAX_ERR, tok->value, SYNTAX_ERR_LEN, 1), -1);
	}
	else if (is_redirector(*tok) && t != T_HERDOC)
	{
		if (!next || next->type != T_UNKNOWN)
			return (throw_error(SYNTAX_ERR, "newline", SYNTAX_ERR_LEN, 1), -1);
	}
	else if (t == T_PARENTHESIS_COMMAND)
	{
		if (next && (next->type != T_AND
				&& next->type != T_OR && next->type != T_PIPE))
			return (throw_error(SYNTAX_ERR, ")", SYNTAX_ERR_LEN, 1), -1);
	}
	else if (t != T_AND || t != T_OR || t != T_PIPE)
	{
		if (next && next->type == T_PARENTHESIS_COMMAND)
			return (throw_error(SYNTAX_ERR, "(", SYNTAX_ERR_LEN, 1), -1);
	}
	return (0);
}

int	more_tokenization(t_memsession *session, t_token **toks, int i)
{
	int	res;

	res = 0;
	while (toks[++i])
	{
		if (toks[i]->type == T_HERDOC)
		{
			if (!toks[i + 1] || toks[i + 1]->type != T_UNKNOWN)
				return (throw_error(SYNTAX_ERR, "newline",
						SYNTAX_ERR_LEN, 1), -1);
			handle_heredoc(session, toks[i + 1]);
			res = session->envs->exit_status;
		}
		if (res != 0)
			return (2);
		res = check_syntax(toks[i], toks[i]->type, toks[i + 1], i);
		if (res != 0)
			return (res);
	}
	return (res);
}

/*
* In this part we identifie the operators specefically 
*/
t_token	**tokenization(t_memsession *session, t_splitdata *splited_cmd)
{
	int		i;
	t_token	**toks;

	toks = session_malloc(session,
			(splited_cmd->word_count + 1) * sizeof(t_token *), 0);
	i = -1;
	while (++i < splited_cmd->word_count)
		(1) && (toks[i] = session_malloc(session, sizeof(t_token), 0),
			toks[i]->tokens_nbr = splited_cmd->word_count,
				toks[i]->value = splited_cmd->words[i], toks[i]->command = 1,
					toks[i]->type = get_token_type(splited_cmd->words[i]));
	(1) && (toks[i] = NULL, i = -1);
	while (++i < toks[0]->tokens_nbr)
		if (toks[i]->type != T_WORD && !is_redirector(*(toks[i]))
			&& toks[i]->type != T_PARENTHESIS_COMMAND
			&& new_is_ops(toks[i]->value))
			toks[i]->command = 0;
	i = more_tokenization(session, toks, -1);
	if (i != 0)
	{
		(i != 2) && (session->envs->exit_status = 1);
		return (NULL);
	}
	return (toks);
}

void	spliting_process(t_memsession *session,
	t_splitdata *result, char *str, char *seps)
{
	int		i;
	char	tmp;

	i = 0;
	while (*str && i < result->word_count)
	{
		(new_is_ops(str)) && (result->words[i++] = ops_strdup(session, &str));
		if (*str && !new_sep_check(str, seps))
		{
			result->words[i++] = custom_strdup(session, str, seps);
			while (*str && !new_sep_check(str, seps))
			{
				if (*str == '"' || *str == '\'')
				{
					tmp = *(str++);
					while (*(str++) != tmp)
						;
				}
				else
					str++;
			}
		}
		(*str && !new_is_ops(str)) && (str++);
	}
	result->words[i] = NULL;
}

/*
* It returns a data structure that have as members :
* 	- word_count : the number of slitted strings
*	- words : the array of strings that has the splitted strings
*/
t_token	**advanced_split(t_memsession *session, char *str, char *seps)
{
	t_splitdata	*result;
	t_splitdata	*tmp;
	t_token		**tokens;

	if (!str || !seps)
		return (NULL);
	result = session_malloc(session, sizeof(t_splitdata), 0);
	tmp = result;
	result->word_count = ft_count_words(str, seps);
	if (result->word_count == 0)
		return (NULL);
	result->words = session_malloc(session,
			(result->word_count + 1) * sizeof(char *), 0);
	spliting_process(session, result, str, seps);
	tokens = tokenization(session, tmp);
	return (tokens);
}
