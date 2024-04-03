/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:30:47 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/02 21:23:19 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

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
		if (close > open)
			return (write(2, "Syntax error: related to parenthesis\n", 37), 1);
		i++;
	}
	if (close != open)
		return (write(2, "Syntax error: related to parenthesis\n", 37), 1);
	return (0);
}

int	check_if_quotes_closed(char *s)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (s[i])
	{
		if (s[i] == '"')
			d_quotes++;
		else if (s[i] == '\'')
			s_quotes++;
		i++;
	}
	if (s_quotes % 2 || d_quotes % 2)
		return (write(2, "Syntax error: related to quotes\n", 32), 1);
	return (0);
}

void	handle_prompt(t_memsession *heap_session, char *prompt)
{
	t_token	*tokens; // array of tokens

	if (check_if_parenthesis_closed(prompt) || check_if_quotes_closed(prompt))
		return ;
	tokens = ms_lexer(heap_session, prompt);
	// handle_commands();
}
