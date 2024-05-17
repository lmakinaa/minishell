/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_control_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:38 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/17 15:45:45 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*get_value(t_memsession *session, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_strdup(session, str + i, ft_strlen(str) - i));
		}
		i++;
	}
	return (NULL);
}

char	*get_name(t_memsession *session, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '=')
			return (ft_strdup(session, str, i - 1));
		i++;
	}
	return (ft_strdup(session, str, ft_strlen(str)));
}

// to remove
void	envs_display(t_lenv *list)
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
	printf("The head's content-->[%s=%s]\n",
		list->head->name, list->head->value);
	after_head = list->head->next;
	i = 2;
	if (after_head)
	{
		while (after_head->next)
		{
			printf("[%d]-->[%s=%s]\n", i, after_head->name,
				after_head->value);
			after_head = after_head->next;
			i++;
		}
	}
	printf("The tail's content-->[%s=%s]\n", list->tail->name,
		list->tail->value);
}

void	append_env(t_memsession *session, t_lenv *envs, char *name, char *value)
{
	t_env	*head;

	head = envs->head;
	while (head)
	{
		if (!ft_strcmp(1, name, head->name))
		{
			head->value = ft_strjoin(session, head->value, value);
			return ;
		}
		head = head->next;
	}
	if (!value)
		value = ft_strdup(session, "", 0);
	create_env(session, envs, name, value);
	envs->count++;
}
