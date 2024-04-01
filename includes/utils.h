/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:41:27 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/01 23:54:49 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "allocation_manager.h"

/*
* This is a struct used only for advanced_split(), it have 2 members :
*	- words : array of splitted strings
*	- word_count : amount of strings splitted
*/
typedef struct s_splitted
{
	char	**words;
	int		word_count;
}		t_splitdata;

int			ft_strcmp(char *str, char *compared_to);
t_splitdata	*advanced_split(t_memsession *session, char *str, char *seps);
int			ft_strlen(char *str);
char		*ft_strchr(char *s, int c);
int			sep_check(char c, char *seps);
int			ft_count_words(char *str, char *seps);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strdup(char *s1);
char		*ft_substr(char *s, unsigned int start, size_t len);

#endif