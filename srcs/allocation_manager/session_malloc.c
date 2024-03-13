/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:33:17 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/13 21:16:17 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/allocation_manager.h"

/*
* Allocate memory and store the address in the session struct
*/
void	*session_malloc(t_memsession *session, size_t size)
{
	t_memslot	*new_slot;

	new_slot = malloc(sizeof(t_memslot));
	if (!new_slot)
		return (session_destroy(&session), exit_on_alloc_error(), NULL);
	new_slot->addr = malloc(size);
	if (!new_slot->addr)
		return (session_destroy(&session), exit_on_alloc_error(), NULL);
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
	return (new_slot->addr);
}
