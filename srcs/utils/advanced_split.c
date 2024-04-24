/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:03:09 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/24 19:20:38 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_token	**handle_heredoc(t_memsession *session, t_token **toks, int i)
{
	int		fds[2];
	char	*line;
	char	*file;
	
	file = ft_strdup(session, "", 0);
	while (toks[++i])
		if (toks[i]->type == T_HERDOC)
		{
			if (!toks[i + 1] || !is_word(toks[i + 1]))
				return (syntax_error("near <<", 7), NULL);
			(pipe(fds) == -1) && (exit_on_error("pipe() failed\n", 14), 0);
			while (1)
			{
				line = readline("# ");
				add_to_session(session, line);
				if (!ft_strcmp(line, toks[i + 1]->value))
					break;
				file = ft_strjoin(session, file, line);
				file = ft_joinchar(session, file, '\n');
			}
			write(fds[1], file, ft_strlen(file));
			(close(fds[1]), toks[i]->value[0] = fds[0]);
			toks[i]->type = T_STD_INPUT;
		}
	return (toks);
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
	{
		toks[i] = session_malloc(session, sizeof(t_token), 0);
		toks[i]->tokens_nbr = splited_cmd->word_count;
		toks[i]->type = get_token_type(splited_cmd->words[i]);
		toks[i]->value = splited_cmd->words[i];
		toks[i]->command = 1;
	}
	toks[i] = NULL;
	i = -1;
	while (++i < toks[0]->tokens_nbr)
		if (toks[i]->type != T_WORD && !is_redirector(*(toks[i]))
			&& toks[i]->type != T_PARENTHESIS_COMMAND && new_is_ops(toks[i]->value))
			toks[i]->command = 0;
	return (handle_heredoc(session, toks, -1));
}

void	spliting_process(t_memsession *session,
	t_splitdata *result, char *str, char *seps)
{
	int		i;
	char	tmp;

	i = 0;
	while (*str && i < result->word_count)
	{
		if (new_is_ops(str))
			result->words[i++] = operators_strdup(session, &str);
		if (*str && !new_sep_check(str, seps))
		{
			result->words[i++] = custom_strdup(session, str, seps);
			while (*str && !new_sep_check(str, seps))
				if (*str == '"' || *str == '\'')
				{
					tmp = *str;
					while (*(++str) && *str != tmp)
						;
				}
				else
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
