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

void	handle_prompt(t_memsession *heap_session, char *prompt)
{
	t_token	**tokens; // array of tokens
	t_tnode	*root;

	if (check_if_parenthesis_closed(prompt))
		return ;
	tokens = ms_lexer(heap_session, prompt);
	// print_tokens(tokens);
	root = build_tree(heap_session, &tokens, 0);
	print_tree(root, 0);
	// handle_commands();
}
