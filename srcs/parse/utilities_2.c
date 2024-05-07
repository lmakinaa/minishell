/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:43:23 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/07 16:39:59 by ijaija           ###   ########.fr       */
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

/*
* if 2 is passed in the perror will print the error and
* the two args (len and arg) will be ignored
*/
void	throw_error(char *error, char *arg, int len, int type)
{
	if (type != 2)
	{
		write(2, "minishell: ", 11);
		if (type == 1)
			write(2, "syntax error ", 13);
		write(2, error, len);
		if (arg)
			(1) && (write(2, " `", 2), write(2, arg, ft_strlen(arg)),
				write(2, "'", 1));
		write(2, "\n", 1);
	}
	else if (type == 2)
	{
		write(2, "minishell: ", 11);
		perror(error);
	}
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
