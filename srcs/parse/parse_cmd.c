/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:18:48 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/17 14:30:50 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static char	*add_var_quotes(t_memsession *s, char *str)
{
	char	*res;

	res = ft_strdup(s, "\"", 0);
	res = ft_strjoin(s, res, str);
	res = ft_joinchar(s, res, '\"');
	del_from_session(s, str);
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
	char 	*out_type;
	char	**out_files;
	char	*input_file;
	int		std_input;
	
	i = -1;
	out_type = ft_strdup(session, "", 0);
	input_file = NULL;
	out_files = NULL;
	std_input = -1;
	while (cmd && cmd[++i])
		if (cmd[i]->type == T_OUT_REDIR || cmd[i]->type == T_APPEND_REDIR)
			out_type = ft_joinchar(session, out_type, cmd[i]->type);
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
	res->path = NULL;
}

static int	ft_part2(t_memsession *session, t_command *res, t_token **cmd)
{
	parse_cmd_2(session, res, cmd);
	if (res->args)
		if (get_path(res) == -1)
			return (-1);
	return (0);
}

t_command *parse_cmd(t_memsession *session, t_lenv *env, t_token **cmd)
{
	t_command	*res;
	t_splitdata	*d;
	char		**words;
	int			i;

	(1) && (res = session_malloc(session, sizeof(t_command), 0), res->env = env,
		res->session = session, res->argc = 0, res->args = NULL, i = -1);
	while (cmd && cmd[++i])
		if (cmd[i]->type == T_UNKNOWN || cmd[i]->type == T_VAR)
		{
			if (i > 0 && !ft_strcmp(1, cmd[0]->value, "export"))
				d = ft_split(session, cmd[i]->value, "");
			else
				d = ft_split(session, cmd[i]->value, SEPERATORS);
			words = d->words;
			while (*words && ++res->argc)
			{
				((cmd[i]->type == T_VAR) && (*words = add_var_quotes(session, *words)));
				res->args = append_arg(session, res->args,
					no_quotes(session, *(words++), 0), 0);
			}
		}
	if (ft_part2(session, res, cmd) == -1)
		return (NULL);
	return (res);
}
