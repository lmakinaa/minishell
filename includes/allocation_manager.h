/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_manager.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:27:54 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 12:25:47 by ijaija           ###   ########.fr       */
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

# define MALLOC_ERR "Error while allocation\n"
# define ADDR_ADD_ERR "Error trying to add a null pointer to session struct\n"

void	exit_on_alloc_error(char *error, int len);
void	session_init(t_memsession **session_ptr);
void	*session_malloc(t_memsession *session, size_t size);
void	session_destroy(t_memsession **session_ptr);
void	reset_session(t_memsession **session_ptr);
void	add_to_session(t_memsession *session, void *address);

#endif