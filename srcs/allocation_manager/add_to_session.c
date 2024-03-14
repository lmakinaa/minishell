/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_session.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:14:41 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 12:25:18 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/allocation_manager.h"

void	add_to_session(t_memsession *session, void *address)
{
	t_memslot	*new_slot;

	if (!address)
		return (session_destroy(&session),
			exit_on_alloc_error(ADDR_ADD_ERR, 53));
	new_slot = malloc(sizeof(t_memslot));
	if (!new_slot)
		return (session_destroy(&session), exit_on_alloc_error(MALLOC_ERR, 23));
	new_slot->addr = address;
	new_slot->next = NULL;
	if (!session->first)
	{
		session->first = new_slot;
		session->last = new_slot;
	}
	else
	{
		session->last->next = new_slot;
		session->last = new_slot;
	}
	session->count++;
}
