/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:33:17 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/04 01:07:08 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/allocation_manager.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

/*
* Allocate memory and store the address in the session struct
* It will erase the memory data (ft_bzero()) if 1 is passed in the last param
*/
void	*session_malloc(t_memsession *session, size_t size, int erase)
{
	t_memslot	*new_slot;

	new_slot = malloc(sizeof(t_memslot));
	if (!new_slot)
		return (session_destroy(&session), exit_on_error(MALLOC_ERR, 23), NULL);
	new_slot->addr = malloc(size);
	if (!new_slot->addr)
		return (session_destroy(&session), exit_on_error(MALLOC_ERR, 23), NULL);
	if (erase)
		ft_bzero(new_slot->addr, size);
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
