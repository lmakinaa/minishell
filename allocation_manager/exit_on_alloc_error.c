/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_on_alloc_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:43:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/11 14:55:23 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation_manager.h"

/*
* Writes an error message and exit the program
*/
void	exit_on_alloc_error(void)
{
	write(2, "Error while allocation\n", 23);
	exit(1);
}
