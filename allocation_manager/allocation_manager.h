/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_manager.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:27:54 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/13 15:59:00 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATION_MANAGER_H
# define ALLOCATION_MANAGER_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_heapaddr
{
	void				*addr;
	struct s_heapaddr	*next;
}			t_memslot;

typedef struct s_heapslots
{
	struct s_heapaddr	*first;
	struct s_heapaddr	*last;
	int					count;
}			t_memsession;

void	exit_on_alloc_error(void);
void	session_init(t_memsession **session_ptr);
void	*session_malloc(t_memsession *session, size_t size);
void	session_destroy(t_memsession **session_ptr);
void	reset_session(t_memsession **session_ptr);

#endif