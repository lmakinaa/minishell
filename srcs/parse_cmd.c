/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:18:48 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/26 14:44:25 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char *get_exec(char *value)
{
	char *res;

	res = value;
	while (*value)
	{
		if (*value == '/')
			res = value + 1;
		value++;
	}
	if (!*res)
		return (NULL);
	return (res);
}

char	**append_arg(t_memsession *session, char **args, char *value, int cmd)
{
	char	**res;
	int		i;
	int		j;
	
	if (!args)
	{
		res = session_malloc(session, 2 * sizeof(char *), 0);
		res[0] = value;
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
	if (cmd)
		res[j++] = value;
	else
		res[j++] = value;
	res[j] = NULL;
	del_from_session(session, args);
	return (res);
}

void	parse_cmd_2(t_memsession *session, t_command *res, t_token **cmd)
{
	int		i;
	int 	out_type;
	char	**out_files;
	char	*input_file;
	int		std_input;
	
	i = -1;
	out_type = -1;
	input_file = NULL;
	out_files = NULL;
	std_input = -1;
	while (cmd[++i])
		if (cmd[i]->type == T_OUT_REDIR || cmd[i]->type == T_APPEND_REDIR)
			out_type = cmd[i]->type;
		else if (cmd[i]->type == T_OUTPUT_FILE)
			out_files = append_arg(session, out_files, cmd[i]->value, 0);
		else if (cmd[i]->type == T_INPUT_FILE)
			input_file = cmd[i]->value;
		else if (cmd[i]->type == T_STD_INPUT)
			std_input = cmd[i]->value[0];
	res->input_file = input_file;
	res->output_redir_type = out_type;
	res->output_files = out_files;
	res->std_input = std_input;
}

t_command *parse_cmd(t_memsession *session, t_lenv *env, t_token **cmd)
{
	t_command	*res;
	t_splitdata	*d;
	char		**words;
	int			i;
	int			j;

	res = session_malloc(session, sizeof(t_command), 0);
	res->env = env;
	res->args = NULL;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN)
		{
			d = ft_split(session, cmd[i]->value, SEPERATORS);
			words = d->words;
			j = -1;
			while (*words)
				res->args = append_arg(session, res->args, *(words++), 0);
		}
	}
	parse_cmd_2(session, res, cmd);
	return (res);
}
