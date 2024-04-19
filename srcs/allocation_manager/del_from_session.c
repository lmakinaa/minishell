/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_from_session.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:32:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/19 19:55:16 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static void	del_from_session_part2(t_memsession *session, void *addr)
{
	t_memslot	*tmp;
	t_memslot	*first_node;
	
	first_node = session->first;
	while (first_node->next)
	{
		if (first_node->next->addr == addr)
		{
			tmp = first_node->next->next;
			free(first_node->next->addr);
			free(first_node->next);
			first_node->next = tmp;
		}
		first_node = first_node->next;
	}
	session->count--;
}

/*
* Free a single address and removes it from the session list
*/
void	del_from_session(t_memsession *session, void *addr)
{
	t_memslot	*tmp;

	if (!addr)
		return ;
	if (session->first->addr == addr && session->first->next)
	{
		tmp = session->first->next;
		free(session->first->addr);
		free(session->first);
		session->first = tmp;
		session->count--;
	}
	else if (session->first->addr == addr && !session->first->next)
	{
		free(session->first->addr);
		free(session->first);
		session->first = NULL;
		session->last = NULL;
		session->count--;
	}
	else
		del_from_session_part2(session, addr);
}
