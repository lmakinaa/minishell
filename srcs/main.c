/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:03 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/19 16:55:14 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	g_sig;

char	*generate_prompt(t_memsession *session, t_lenv *env)
{
	char	*buffer;
	char	*tmp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	tmp = ft_strnstr(cwd, get_env(env, "HOME"), ft_strlen(cwd));
	buffer = ft_strdup(session, "\e[0;33m", 7);
	if (tmp)
	{
		buffer = ft_joinchar(session, buffer, '~');
		buffer = ft_strjoin(session, buffer, tmp);
	}
	else
		buffer = ft_strjoin(session, buffer, cwd);
	buffer = ft_strjoin(session, buffer, " \e[1;30m> \033[0m");
	free(cwd);
	return (buffer);
}

//void	f(void)
//{
//	system("leaks minishell");
//}

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

void	sig_n_term_init(t_lenv *env)
{
	struct termios	termios;

	termios = env->initial_termios;
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
	g_sig = 0;
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	t_memsession	*main_session;
	t_memsession	*env_session;
	t_lenv			*env;
	char			*command;

	(void) argc;
	env = ft_initialise(&main_session, &env_session, argv, envp);
	while (1)
	{
		sig_n_term_init(env);
		command = readline(generate_prompt(main_session, env));
		if (!command)
			break ;
		add_to_session(main_session, command);
		ft_addhistory(command);
		handle_prompt(main_session, env, command);
		reset_session(&main_session);
	}
	rl_clear_history();
	end_sessions(&main_session, &env_session);
	tcsetattr(STDIN_FILENO, TCSANOW, &env->initial_termios);
	return (0);
}
