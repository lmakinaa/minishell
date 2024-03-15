/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:30:47 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/15 22:11:52 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

// this to view the list of tokens :
// int i = -1;
// while (++i < tokens->tokens_nbr)
// {
// 	printf("\t[%d] : \n%s\n%d\n%d\n%d\n", tokens[i].order, tokens[i].value, tokens[i].len,
// 		tokens[i].type, tokens[i].tokens_nbr);
// }
void	handle_command(t_memsession *heap_session, char *command)
{
	t_token	*tokens;

	tokens = ms_lexer(heap_session, command);
	
}
