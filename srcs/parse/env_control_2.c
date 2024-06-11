/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_control_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:28:38 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/20 16:02:29 by ijaija           ###   ########.fr       */
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
