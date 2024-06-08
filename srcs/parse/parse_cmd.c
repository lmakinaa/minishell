/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:18:48 by ijaija            #+#    #+#             */
/*   Updated: 2024/06/09 00:37:56 by ijaija           ###   ########.fr       */
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

void	parse_cmd_2(t_memsession *session, t_command *res, t_token **cmd, int i)
{
	char	*out_type;
	char	**out_files;
	char	*input_file;
	int		std_input;
	int		tmp;

	(1) && (tmp = -1, out_type = ft_strdup(session, "", 0), input_file = NULL,
		out_files = NULL, std_input = -1);
	while (cmd && cmd[++i])
		if (cmd[i]->type == T_OUT_REDIR || cmd[i]->type == T_APPEND_REDIR)
			out_type = ft_joinchar(session, out_type, cmd[i]->type);
	else if (cmd[i]->type == T_OUTPUT_FILE)
		out_files = append_arg(session, out_files, cmd[i]->value, 0);
	else if (cmd[i]->type == T_INPUT_FILE)
		(1) && (input_file = cmd[i]->value, tmp = i);
	else if (cmd[i]->type == T_STD_INPUT)
		(i > tmp) && (input_file = cmd[i]->value);
	(1) && (res->input_file = input_file, res->output_redir_type = out_type,
		res->output_files = out_files, res->std_input = -1,
		res->path = NULL);
}

static int	ft_part2(t_memsession *session, t_command *res, t_token **cmd)
{
	parse_cmd_2(session, res, cmd, -1);
	if (res->args && !res->args[0][0])
	{
		s_s(session->envs, 127);
		throw_error(":command not found", 0, 18, 0);
		return (-1);
	}
	else if (res->args)
		if (get_path(res) == -1)
			return (-1);
	return (0);
}

void	expand_splited(t_memsession *s, char ***w, t_splitdata *d)
{
	char		**words;
	t_splitdata	*tmp;
	char		**res;
	int			i;

	*w = d->words;
	words = *w;
	i = 0;
	res = NULL;
	while (words[i])
	{
		words[i] = expand_2(s, words[i]);
		tmp = ft_split(s, words[i], SEPERATORS);
		if (tmp->word_count > 1)
			res = append_arr(s, res, tmp->words, tmp->word_count);
		else
			res = append_arg(s, res, words[i], 0);
		i++;
	}
	del_from_session(s, *w);
	*w = res;
}

t_command	*parse_cmd(t_memsession *session, t_lenv *env, t_token **cmd, int i)
{
	t_command	*res;
	t_splitdata	*d;
	char		**words;

	(1) && (res = session_malloc(session, sizeof(t_command), 0), res->env = env,
		res->session = session, res->argc = 0, res->args = NULL);
	while (cmd && cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN || cmd[i]->type == T_VAR)
		{
			if (i > 0 && !ft_strcmp(1, cmd[0]->value, "export"))
				d = ft_split(session, cmd[i]->value, "");
			else
				d = ft_split(session, cmd[i]->value, SEPERATORS);
			expand_splited(session, &words, d);
			while (words && *words && ++res->argc)
				(1) && (((cmd[i]->type == T_VAR)
					&& (*words = add_var_quotes(session, *words))),
					res->args = append_arg(session, res->args,
						no_quotes(session, *(words++), 0), 0));
		}
	}
	if (ft_part2(session, res, cmd) == -1)
		return (NULL);
	return (res);
}
