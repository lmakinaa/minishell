/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:03:17 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/06 18:08:44 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_tnode	*create_node(t_memsession *session, t_token *token)
{
	t_tnode	*res;

	res = session_malloc(session, sizeof(t_tnode), 0);
	res->token = token;
	res->left = NULL;
	res->right = NULL;
	return (res);
}
