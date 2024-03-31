/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 21:57:04 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/31 22:14:09 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static char	*fetch_type(int	type)
{
	if (type == T_REDIRECTORS)
		return ("Redirectors");
	else if (type == T_EXECUTABLE)
		return ("Executable");
	else if (type == T_BUILTIN)
		return ("Builtin");
	else if (type == T_ARG)
		return ("Argument");
	else if (type == T_FLAG)
		return ("Flag");
	else if (type == T_QUOTES)
		return ("Quotes");
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
	else
		return ("Unknown");
}

/*
* Print all the tokens (the elements of -t_token *tokens-)
* It is not protected! use it only for testing.
*/
void	print_tokens(t_token *tokens)
{
	int i;

	i = -1;
	if (tokens)
		printf("tokens_nbr––>%d\n\n––––––––\n\n", tokens[0].tokens_nbr);
	while (++i < tokens->tokens_nbr)
	{
		printf("order––>[%d]\nvalue––>%s\nlen––>%d\ntype––>%s\n\n––––––––\n\n",
			tokens[i].order,
			tokens[i].value,
			tokens[i].len,
			fetch_type(tokens[i].type));
	}
}
