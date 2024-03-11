/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_on_alloc_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:43:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/11 11:45:10 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation_manager.h"

void	exit_on_alloc_error(void)
{
	write(2, "Error while allocation\n", 23);
	exit(1);
}
