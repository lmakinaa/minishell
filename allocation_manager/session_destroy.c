/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:03:43 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/11 12:27:47 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation_manager.h"

void	session_destroy(t_memsession **session_ptr)
{
	t_memslot	*first_node;
	t_memslot	*tmp;
	int			i;

	if (!(*session_ptr)->first)
		return (free(*session_ptr));
	first_node = (*session_ptr)->first;
	i = -1;
	while (++i < (*session_ptr)->count)
	{
		tmp = first_node;
		first_node = first_node->next;
		free(tmp->addr);
		free(tmp);
	}
	free(*session_ptr);
}
