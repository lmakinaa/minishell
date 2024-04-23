/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:18:48 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/23 20:05:07 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char *get_exec(char *value)
{
	char *res;

	if (*value == '\0')
		return (NULL);
	while (*value)
	{
		if (*value == '/')
		{
			value++;
			res = get_exec(value);
			if (res == NULL)
				return (value);
			else
				return (res);
		}
		value++;
	}
	return (value);
}

char	**append_arg(t_memsession *session, char **args, char *value, int cmd)
{
	char	**res;
	int		i;
	int		j;
	
	if (!args)
	{
		res = session_malloc(session, 2 * sizeof(char *), 0);
		res[0] = get_exec(value);
		res[1] = NULL;
		return (res);
	}
	i = 0;
	while (args[i])
		i++;
	res = session_malloc(session, (i + 2) * sizeof(char *), 0);
	j = -1;
	while (++j < i)
		res[j] = args[j];
	res[j++] = get_exec(value);
	res[j] = NULL;
	del_from_session(session, args);
	return (res);
}

t_command *parse_cmd(t_memsession *session, t_lenv *env, t_token **cmd)
{
	t_command	*res;
	int			i;

	res = session_malloc(session, sizeof(t_command), 0);
	res->env = env;
	res->args = NULL;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_CMD)
		{
			res->cmd = cmd[i]->value;
			res->args = append_arg(session, res->args, cmd[i]->value, 1);
		}
		else if (cmd[i]->type == T_ARG)
			res->args = append_arg(session, res->args, cmd[i]->value, 0);
	}
	parse_cmd_2(session, res, cmd);
	return (res);
}
