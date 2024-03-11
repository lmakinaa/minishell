/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:51:33 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/11 14:57:11 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation_manager.h"

/*
* Initialise the allocation session structure
*/
void	session_init(t_memsession **session_ptr)
{
	t_memsession	*session;

	session = malloc(sizeof(t_memsession));
	if (!session)
		exit_on_alloc_error();
	session->first = NULL;
	session->last = NULL;
	session->count = 0;
	*session_ptr = session;
}
