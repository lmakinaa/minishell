/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtalbi <mtalbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:09:40 by mtalbi            #+#    #+#             */
/*   Updated: 2024/06/08 18:06:19 by mtalbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	b_env(t_command *command)
{
	t_env	*head;

	head = command->env->head;
	while (head)
	{
		if (head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	return (0);
}
