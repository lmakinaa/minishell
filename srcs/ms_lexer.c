/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:04:32 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 15:54:11 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_token	*ms_lexer(t_memsession *session, char *command)
{
	t_token		*res;
	t_splitdata	*splited_cmd;
	int			i;

	splited_cmd = advanced_split(session, command, SEPERATORS);
	res = session_malloc(session, splited_cmd->word_count * sizeof(t_token));
	i = -1;
	while (++i < splited_cmd->word_count)
	{
		res[i].data = splited_cmd->words[i];
		
	}
	
}
