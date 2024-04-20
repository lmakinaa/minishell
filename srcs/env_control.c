/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:23:24 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/20 20:13:35 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_lenv	*envs_init(t_memsession *session, char **envp)
{
	t_lenv	*res;
	char	*name;
	char	*value;
	int		i;

	res = session_malloc(session, sizeof(t_lenv), 0);
	res->head = NULL;
	res->tail = NULL;
	i = -1;
	while (envp[++i])
	{
		name = z_strdup(session, &envp[i], "=");
		(envp[i])++;
		value = z_strdup(session, &envp[i], "\0");
		add_env(session, res, name, value);
	}
	return (res);
}

t_env *create_env(t_memsession *session, char *name, char *value)
{
	t_env *res;

	res = session_malloc(session, sizeof(t_env), 0);
	res->name = name;
	res->value = value;
	res->next = NULL;
	return (res);
}

void add_env(t_memsession *session, t_lenv *envs, char *name, char *value)
{
	t_env	*node;
	
	node = create_env(session, name, value);
	if (!envs->head)
	{
		envs->head = node;
		envs->tail = node;
		return ;
	}
	envs->tail->next = node;
	envs->tail = node;
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
		return(del_node(session, f_env));
	}
	while (f_env->next)
	{
		if (!ft_strcmp(f_env->next->name, name))
		{
			tmp = f_env->next->next;
			del_node(session, f_env->next);
			f_env->next = tmp;
			return ;
		}
		f_env = f_env->next;
	}
}

// to remove
void envs_display(t_lenv *list)
{
	t_env	*after_head;
	int		i;

	if (!list)
	{
		printf("The list is empty!\n");
		return ;
	}
	if (!list->head)
	{
		printf("The list have no head!\n");
		return ;
	}
	if (!list->tail)
	{
		printf("The list have no tail!\n");
		return ;
	}
	printf("The head's content-->[%s=%s]\n", list->head->name, list->head->value);
	after_head = list->head->next;
	i = 2;
	if (after_head)
	{
		while (after_head->next)
		{
			printf("[%d]-->[%s=%s]\n", i, after_head->name, after_head->value);
			after_head = after_head->next;
			i++;
		}
	}
	printf("The tail's content-->[%s=%s]\n", list->tail->name, list->tail->value);
}
