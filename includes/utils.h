/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:41:27 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 14:54:10 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "allocation_manager.h"

typedef struct s_splitted
{
	char	**words;
	int		word_count;
}		t_splitdata;

int			ft_strcmp(char *str, char *compared_to);
t_splitdata	*advanced_split(t_memsession *session, char *str, char *seps);

#endif