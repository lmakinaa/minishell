/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:30:47 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/31 22:07:18 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	handle_command(t_memsession *heap_session, char *command)
{
	t_token	*tokens; // array of tokens

	tokens = ms_lexer(heap_session, command);
	print_tokens(tokens);
}
