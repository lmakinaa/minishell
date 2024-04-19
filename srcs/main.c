/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:03 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 13:25:45 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

//int argc, char **argv, char **env

int	main(void)
{
	t_memsession	*heap_session;
	char			*command;

	session_init(&heap_session);
	while (1)
	{
		command = readline(PROMPT_TEXT);
		if (!command)
			break ;
		add_to_session(heap_session, command);
		add_history(command);
		handle_prompt(heap_session, command);
		reset_session(&heap_session);
	}
	rl_clear_history();
	session_destroy(&heap_session);
	return (0);
}
