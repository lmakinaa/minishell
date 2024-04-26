/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:43:23 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/26 20:54:41 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	new_sep_check(char *c, char *seps)
{
	int	i;

	i = -1;
	while (seps[++i])
		if (seps[i] == *c || new_is_ops(c))
			return (1);
	return (0);
}

void	throw_error(char *error, int len, int syntax)
{
	write(2, "minishell: ", 11);
	if (syntax)
		write(2, "syntax error ", 13);
	write(2, error, len);
	write(2, "\n", 1);
}

int	is_word(t_token	*tok)
{
	if (is_redirector(*tok) || tok->type != T_PARENTHESIS_COMMAND
		|| !tok->command)
		return (1);
	return (0);
}

void	void_return(void)
{
	return ;
}
