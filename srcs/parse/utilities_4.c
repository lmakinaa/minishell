/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:43:18 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/21 12:48:43 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	sig_handle(int num)
{
	if (g_sig == 2)
	{
		close(0);
		g_sig = 3;
		return ;
	}
	if (num == SIGINT)
	{
		write(1, "\n", 1);
		if (g_sig == 1)
			return ((1) && (g_sig = 0), void_return());
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (num == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		reset_terminal(NULL);
	}
}

/*
* it focuses on redirections
*/
int	tokenize_part2(t_token **cmd)
{
	int	i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i]->type == T_OUT_REDIR || cmd[i]->type == T_APPEND_REDIR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (throw_error(SYNTAX_ERR, cmd[i]->value, 21, 1), -1);
			cmd[i + 1]->type = T_OUTPUT_FILE;
		}
		else if (cmd[i]->type == T_INPUT_REDIRECTOR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (throw_error(SYNTAX_ERR, "<", 21, 1), -1);
			cmd[i + 1]->type = T_INPUT_FILE;
		}
	}
	return (0);
}

char	*get_exec(char *value)
{
	char	*res;

	res = value;
	while (*value)
	{
		if (*value == '/')
			res = value + 1;
		value++;
	}
	if (!*res)
		return (NULL);
	return (res);
}

char	*get_env(t_lenv *env, char *name)
{
	t_env	*f_env;

	if (!env || !env->head)
		return (NULL);
	f_env = env->head;
	while (f_env)
	{
		if (!ft_strcmp(1, f_env->name, name))
			return (f_env->value);
		f_env = f_env->next;
	}
	return (NULL);
}

char	*get_exit_status(t_memsession *session, t_lenv *env)
{
	char		*res;
	int			code;
	int			i;

	res = session_malloc(session, 4 * sizeof(char), 0);
	code = env->exit_status;
	i = 0;
	while (code / 10)
		(1) && (code /= 10, i++);
	code = env->exit_status;
	res[i + 1] = '\0';
	while (code / 10)
	{
		res[i--] = (code % 10) + '0';
		code /= 10;
	}
	res[i] = (code % 10) + '0';
	return (res);
}
