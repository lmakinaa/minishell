/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:51:33 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 12:22:17 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/allocation_manager.h"

/*
* Initialise the allocation session structure
*/
void	session_init(t_memsession **session_ptr)
{
	t_memsession	*session;

	session = malloc(sizeof(t_memsession));
	if (!session)
		exit_on_alloc_error(MALLOC_ERR, 23);
	session->first = NULL;
	session->last = NULL;
	session->count = 0;
	*session_ptr = session;
}
