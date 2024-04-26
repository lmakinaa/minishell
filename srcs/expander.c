/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:12:42 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/26 16:30:33 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*var_expansion(t_memsession *session, t_lenv *env, char **str)
{
	char	*new_value;
	char	*var;

	new_value = ft_strdup(session, "", 0);
	while (**str && **str != '"')
	{
		if (**str && **str != '$')
			new_value = ft_joinchar(session, new_value, *((*str)++));
		else if (**str && **str == '$')
		{
			if (*((*str) + 1) && *((*str) + 1) != '$' && (*str)++)
			{
				var = get_env(env, z_strdup(session, str, "$\"'"));
				new_value = ft_strjoin(session, new_value, var);
			}
			else if (**str && **str != '"')
				new_value = ft_joinchar(session, new_value, *((*str)++));
		}
	}
	return (new_value);
}

char	*expand_1(t_memsession *session, t_lenv *env, char *str)
{
	char	*res;
	char	*tmp;

	tmp = str;
	res = ft_strdup(session, "", 0);
	while (*str)
		if (*str == '\'')
		{
			res = ft_joinchar(session, res, *(str++));
			res = ft_strjoin(session, res, z_strdup(session, &str, "'"));
			res = ft_joinchar(session, res, *(str++));
		}
		else if (*str == '"')
		{
			res = ft_joinchar(session, res, *(str++));
			res = ft_strjoin(session, res, var_expansion(session, env, &str));
			res = ft_joinchar(session, res, *(str++));
		}
		else if (*str)
			res = ft_strjoin(session, res, var_expansion(session, env, &str));
	return (del_from_session(session, tmp), res);
}

t_token	**split_append_again(t_memsession *session, t_token **cmds,
	int size, t_token *cmd)
{
	t_token	**toks;
	t_token	**res;
	int		i;
	int		j;

	toks = advanced_split(session, cmd->value, " \t\n");
	if (!toks)
		return (cmds);
	res = session_malloc(session,
		(size + toks[0]->tokens_nbr + 1) * sizeof(t_token *), 0);
	i = -1;
	while (++i < size)
		res[i] = cmds[i];
	j = -1;
	while (++j < toks[0]->tokens_nbr)
		res[i + j] = toks[j];
	res[i + j] = NULL;
	del_from_session(session, cmds);
	del_from_session(session, toks);
	del_from_session(session, cmd);
	return (res);
}

/*
* Expand Vars and whats inside quotes and remove quotes
*/
int	expander(t_memsession *session, t_lenv *env, t_token **cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_UNKNOWN || cmd[i]->type == T_INPUT_FILE
			|| cmd[i]->type == T_OUTPUT_FILE)
		{
			cmd[i]->value = expand_1(session, env, cmd[i]->value);
			cmd[i]->value = expand_2(session, cmd[i]->value);
		}
		if (cmd[i]->type == T_INPUT_FILE || cmd[i]->type == T_OUTPUT_FILE)
			if (ft_countword(cmd[i]->value, SEPERATORS) > 1)
				return (syntax_error("ambiguous redirect", 18), -1);
	}
	return (0);
}
