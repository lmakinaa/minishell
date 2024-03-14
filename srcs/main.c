/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:03 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 14:52:49 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	main(void)
{
	t_memsession	*heap_session;
	char			*command;

	session_init(&heap_session);
	while (1)
	{
		command = readline(PROMPT_TEXT);
		add_to_session(heap_session, command);
		handle_command(heap_session, command);
	}
	
	session_destroy(&heap_session);
}
