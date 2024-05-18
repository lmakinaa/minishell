/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:30:47 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/02 21:23:19 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	handle_prompt(t_memsession *heap_session, t_lenv *env, char *prompt)
{
	t_token	**tokens;
	t_tnode	*root;

	if (are_parenthesis_closed(prompt) || are_quotes_closed(prompt))
	{
		env->exit_status = 258;
		return ;
	}
	tokens = advanced_split(heap_session, prompt, SEPERATORS);
	root = build_tree(heap_session, &tokens, 0);
	int s = execute_tree(heap_session, env, root, 0);
	if (s == -1)
		return ;
}
