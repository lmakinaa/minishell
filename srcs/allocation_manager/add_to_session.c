/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_session.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:14:41 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 17:23:17 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/*
* It adds to the session an address returned by a regular malloc
* and not ours like readline()
* Note: the function will do nothing if a NULL is passed as a second param
*/
void	add_to_session(t_memsession *session, void *address)
{
	t_memslot	*new_slot;

	if (!address)
		return ;
	new_slot = malloc(sizeof(t_memslot));
	if (!new_slot)
		return (session_destroy(&session), exit_on_error(MALLOC_ERR, 23));
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
