/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:04:32 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/15 15:40:40 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_token	*ms_lexer(t_memsession *session, char *command)
{
	t_token		*res;
	t_splitdata	*splited_cmd;
	int			i;

	splited_cmd = advanced_split(session, command, SEPERATORS);
	res = session_malloc(session, (splited_cmd->word_count + 1) * sizeof(t_token));
	i = 0;
	while (splited_cmd->words[i])
	{
		res[i].order = i;
		res[i].value = splited_cmd->words[i];
		res[i].len = ft_strlen(res[i].value);
		res[i].type = get_token_type(res[i].value, res[i].order);
		res[i].tokens_nbr = splited_cmd->word_count;
		i++;
	}
	res[i].value = NULL;
	return (res);
}
