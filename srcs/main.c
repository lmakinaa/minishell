/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:03 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/11 05:36:11 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	f()
{
	system("leaks minishell");
}

void	ft_addhistory(char *command)
{
	int	i;
	
	i = -1;
	while (command[++i] && is_sep(command[i], SEPERATORS))
		;
	if (!command[i])
		return ;
	add_history(command);
}

int	main(int argc, char **argv, char **envp)
{
	t_memsession	*main_session;
	t_memsession	*env_session;
	t_lenv			*env;
	char			*command;

	env = ft_initialise(&main_session, &env_session, argc, argv, envp);
	//envs_display(env);
	while (1)
	{
		command = readline(PROMPT_TEXT);
		if (!command)
			break ;
		add_to_session(main_session, command);
		ft_addhistory(command);
		handle_prompt(main_session, env, command);
		reset_session(&main_session);
	}
	rl_clear_history();
	end_sessions(&main_session, &env_session);
	return (0);
}
