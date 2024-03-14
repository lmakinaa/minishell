/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:11:04 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 12:16:20 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	f()
{
	system("leaks a.out");
}

int	main()
{
	atexit(f);
	char *tt = readline("dfsd ");
	free(tt);
	char *t1 = readline("dfsd ");
	char *tx = (void *) t1;
	free(tx);
	char *t2 = readline("dfsd ");
	free(t2);
	return (0);
}
