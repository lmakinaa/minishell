/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_on_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:43:40 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 12:20:52 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/allocation_manager.h"

/*
* Writes an error message and exit the program
*/
void	exit_on_error(char *error, int len)
{
	write(2, error, len);
	exit(1);
}
