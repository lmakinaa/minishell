/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:11:04 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 14:00:36 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	f()
{
	system("leaks a.out");
}

int	main()
{
	t_token **tt;

	tt = malloc(5 * sizeof(t_token *));
	tt[0]->type = 5;
	tt[1]->type = 6;
	tt[2]->type = 7;
	tt[3]->type = 8;
	printf("%d\n%d\n%d\n", tt[0]->type, tt[1]->type, tt[2]->type);
}
