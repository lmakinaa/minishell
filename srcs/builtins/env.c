/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:09:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/05 11:14:08 by ijaija           ###   ########.fr       */
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
