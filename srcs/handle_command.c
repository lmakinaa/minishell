/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:30:47 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 14:02:40 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	handle_command(t_memsession *heap_session, char *command)
{
	t_token	*tokens;

	tokens = ms_lexer(heap_session, command);
}
