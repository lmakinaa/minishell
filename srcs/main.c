/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:03 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/20 20:14:52 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	f()
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_memsession	*heap_session;
	t_lenv			*envs;
	char			*command;

	(void) argc;
	(void) argv;
	session_init(&heap_session);
	envs = envs_init(heap_session, envp);
	//envs_display(envs);
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
