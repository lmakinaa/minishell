/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:57:04 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/26 20:54:41 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static char	*fetch_type(int type)
{
	if (type == T_APPEND_REDIR)
		return ("Append Redirector");
	else if (type == T_PARENTHESIS_COMMAND)
		return ("Parenthesis command");
	else if (type == T_BUILTIN)
		return ("Builtin");
	else if (type == T_WORD)
		return ("Word");
	else if (type == T_PIPE)
		return ("Pipe");
	else if (type == T_VAR)
		return ("Variable");
	else if (type == T_AUTOMATIC_VAR)
		return ("Automatic Variable");
	else if (type == T_OR)
		return ("Or");
	else if (type == T_AND)
		return ("And");
	else if (type == T_HERDOC)
		return ("Heredoc");
	else if (type == T_INPUT_REDIRECTOR)
		return ("Input Redirector");
	else if (type == T_OUT_REDIR)
		return ("Output Redirector");
	else
		return ("Unknown");
}

/*
* Print all the tokens (the elements of -t_token *tokens-)
* It is not protected! use it only for testing.
*/
void	print_tokens(t_token **tokens)
{
	int i;

	i = -1;
	if (tokens)
		printf("tokens_nbr––>%d\n\n––––––––\n\n", tokens[0]->tokens_nbr);
	while (++i < tokens[0]->tokens_nbr)
	{
		printf("value––>[%s]\ncommand––>%d\ntype––>%s\n\n––––––––\n\n",
			tokens[i]->value,
			tokens[i]->command,
			fetch_type(tokens[i]->type));
	}
}
