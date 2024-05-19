/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:56:03 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/19 12:37:33 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	**generate_env_array(t_memsession *session, t_lenv *env)
{
	char	**res;
	t_env	*head;
	int		i;

	res = session_malloc(session, (env->count + 1) * sizeof(char *), 0);
	i = -1;
	head = env->head;
	while (++i < env->count)
	{
		res[i] = ft_joinchar(session, head->name, '=');
		res[i] = ft_strjoin(session, res[i], head->value);
		head = head->next;
	}
	res[i] = NULL;
	return (res);
}

int	reset_fds(int backup_fds[], int pip)
{
	if (pip)
		return (0);
	if (dup2(backup_fds[0], 0) == -1)
		return (throw_error("dup2", 0, 0, THROW_PERROR), 1);
	close(backup_fds[0]);
	if (dup2(backup_fds[1], 1) == -1)
		return (throw_error("dup2", 0, 0, THROW_PERROR), 1);
	close(backup_fds[1]);
	return (0);
}
