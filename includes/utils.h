/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:41:27 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/16 15:33:02 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "allocation_manager.h"

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
int			ft_count_words(char *str, char *seps);
int			ft_strncmp(char *str, char *compared_to, int n);
int			new_sep_check(char *c, char *seps);
int			new_is_ops(char *c);
int			skip_inside_parenthesis(char **s);
int			ft_strncpy(char *dst, char *src, int n);
char		*shave_parenthesis(t_memsession *session, char *s);
void		parenthesis_strdup(t_memsession *session, char **s, char **r);
char		*operators_strdup(t_memsession *session, char **str);
char		*quotes_strdup(t_memsession *session, char **str, char sep);
char		*custom_strdup(t_memsession *session, char *s, char *seps);

#endif