/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:23:24 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/19 18:12:55 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_lenv	*envs_init(t_memsession *session, char **envp)
{
	t_lenv	*res;
	int		i;

	res = session_malloc(session, sizeof(t_lenv), 0);
	res->head = NULL;
	res->tail = NULL;
	res->session = session;
	res->exit_status = 0;
	tcgetattr(STDIN_FILENO, &res->initial_termios);
	i = -1;
	while (envp[++i])
		add_env(session, res, get_name(session, envp[i]),
			get_value(session, envp[i]));
	res->count = i;
	return (res);
}

t_env	*create_env(t_memsession *session, t_lenv *env, char *name, char *value)
{
	t_env	*res;

	res = session_malloc(session, sizeof(t_env), 0);
	res->name = name;
	res->value = value;
	res->next = NULL;
	if (!env->head)
	{
		env->head = res;
		env->tail = res;
		return (res);
	}
	env->tail->next = res;
	env->tail = res;
	return (res);
}

void	add_env(t_memsession *session, t_lenv *envs, char *name, char *value)
{
	t_env	*head;

	head = envs->head;
	while (head)
	{
		if (!ft_strcmp(1, name, head->name))
		{
			if (value)
				head->value = value;
			return ;
		}
		head = head->next;
	}
	create_env(session, envs, name, value);
	envs->count++;
}

static void	del_node(t_memsession *session, t_env *node)
{
	del_from_session(session, node->name);
	del_from_session(session, node->value);
	del_from_session(session, node);
}

void	remove_env(t_memsession *session, t_lenv *envs, char *name)
{
	t_env	*tmp;
	t_env	*f_env;

	if (!envs->head)
		return ;
	f_env = envs->head;
	if (!ft_strcmp(1, envs->head->name, name))
	{
		if (!envs->head->next)
			envs->tail = NULL;
		envs->head = f_env->next;
		return (envs->count--, del_node(session, f_env));
	}
	while (f_env->next)
	{
		if (!ft_strcmp(1, f_env->next->name, name))
		{
			tmp = f_env->next->next;
			del_node(session, f_env->next);
			envs->count--;
			f_env->next = tmp;
			return ;
		}
		f_env = f_env->next;
	}
}
