/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:04:32 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/03 18:41:56 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_token	*ms_lexer(t_memsession *session, char *command)
{
	t_token		*res;
	t_splitdata	*splited_cmd;
	// int			i;

	splited_cmd = advanced_split(session, command, SEPERATORS);
	// i = -1;
	// while (++i < splited_cmd->word_count)
	// 	printf("%s\n", splited_cmd->words[i]);
	res = NULL;
	return (res);
}
