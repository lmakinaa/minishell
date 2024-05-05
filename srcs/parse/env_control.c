/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:23:24 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/05 18:39:31 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_lenv	*envs_init(t_memsession *session, char **envp)
{
	t_lenv	*res;
	char	*name;
	char	*value;
	int		i;

	res = session_malloc(session, sizeof(t_lenv), 0);
	res->head = NULL;
	res->tail = NULL;
	res->count = 0;
	res->session = session;
	res->exit_status = 0;
	i = -1;
	while (envp[++i])
	{
		name = z_strdup(session, &envp[i], "=");
		(envp[i])++;
		value = z_strdup(session, &envp[i], "\0");
		add_env(session, res, name, value);
		res->count++;
	}
	return (res);
}

t_env *create_env(t_memsession *session, t_lenv *env, char *name, char *value)
{
	t_env *res;

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

void add_env(t_memsession *session, t_lenv *envs, char *name, char *value)
{
	t_env	*head;

	head = envs->head;
	while (head)
	{
		if (!ft_strcmp(name, head->name))
		{
			if (value)
				head->value = value;
			return ;
		}
		head = head->next;	
	}
	create_env(session, envs, name, value);
}

static void	del_node(t_memsession *session, t_env *node)
{
	del_from_session(session, node->name);
	del_from_session(session, node->value);
	del_from_session(session, node);
}

void remove_env(t_memsession *session, t_lenv *envs, char *name)
{
	t_env	*tmp;
	t_env	*f_env;
	
	if (!envs->head)
		return ;
	f_env = envs->head;
	if (!ft_strcmp(envs->head->name, name))
	{
		if (!envs->head->next)
			envs->tail = NULL;
		envs->head = NULL;
		return(envs->count--, del_node(session, f_env));
	}
	while (f_env->next)
	{
		if (!ft_strcmp(f_env->next->name, name))
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
