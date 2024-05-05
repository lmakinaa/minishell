/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:19:49 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/05 19:27:53 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_env	**to_arr(t_lenv *env)
{
	int		i;
	t_env	*head;
	t_env	**res;
	
	res = session_malloc(env->session,
		(env->count + 1) * sizeof(t_env *), 0);
	i = 0;
	head = env->head;
	while (head)
	{
		res[i] = head;
		head = head->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	sort_env(t_lenv *env)
{
	t_env	**arr;
	int		i;
	int		j;
	t_env	*tmp;

	arr = to_arr(env);
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i + (++j)])
			if (ft_strcmp(arr[i]->name, arr[i + j]->name) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + j];
				arr[i + j] = tmp;
			}
	}
	i = -1;
	while (arr[++i])
		arr[i]->index = i;
	del_from_session(env->session, arr);
}
