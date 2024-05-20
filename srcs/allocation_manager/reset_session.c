/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:30:51 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/20 18:12:36 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/*
* Frees up any memory allocated using the session_malloc() function but it
* don't free the session structure that stores the addresses, so that you can
* still use the structure without re-initialising it
*/
void	reset_session(t_memsession **session_ptr)
{
	t_memslot	*first_node;
	t_memslot	*tmp;
	int			i;

	if (!(*session_ptr)->first)
		return ;
	first_node = (*session_ptr)->first;
	i = -1;
	while (++i < (*session_ptr)->count)
	{
		tmp = first_node;
		first_node = first_node->next;
		free(tmp->addr);
		free(tmp);
	}
	(*session_ptr)->first = NULL;
	(*session_ptr)->last = NULL;
	(*session_ptr)->count = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &((*session_ptr)->envs->initial_termios));
}
