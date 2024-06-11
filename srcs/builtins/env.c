/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:09:40 by mtalbi            #+#    #+#             */
/*   Updated: 2024/06/10 16:40:37 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	b_env(t_command *command)
{
	t_env	*head;

	if (command->argc != 1)
		return (throw_error("env accepts no argument", 0, 23, 0), 1);
	head = command->env->head;
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	return (0);
}
