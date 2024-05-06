/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:41:27 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/06 17:57:16 by ijaija           ###   ########.fr       */
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
char		*custom_strdup(t_memsession *session, char *s, char *seps);
char		*custom_strjoin(t_memsession *session, char *s1, char *s2);
char		*ft_strdup(t_memsession *session, char *s1, size_t len);
char		*ft_strjoin(t_memsession *session, char *s1, char *s2);
char		*ft_joinchar(t_memsession *session, char *s1, char c);
int			ft_countword(char *str, char *seps);
t_splitdata	*ft_split(t_memsession *session, char *s, char *seps);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
char		*var_name_strdup(t_memsession *session, char **str);

#endif