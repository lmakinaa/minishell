/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:48:24 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/11 05:49:02 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	dump_err(char *name)
{
	write(2, "minishell: export: `", 20);
	write(2, name, ft_strlen(name));
	write(2, "': not a valid env name\n", 24);
	return (1);
}

static void	dump_list(t_lenv *env)
{
	t_env	*list;
	size_t	i;

	sort_env(env);
	int		j = -1;
	while (++j < env->count)
	{
		list = env->head;
		while (list)
		{
			if (list->index == j && list->value && ft_strcmp(list->name, "_"))
			{
				(void) (write(1, "declare -x ", 11)
					&& write(1, list->name, ft_strlen(list->name)) && write(1, "=\"", 2));
				i = 0;
				while ((list->value)[i])
				{
					if ((list->value[i] == '$' || list->value[i] == '"') && write(1, "\\", 1))
						write(1, &list->value[i++], 1);
					else
						write(1, &list->value[i++], 1);
				}
				write(1, "\"\n", 2);
			}
			else if (list->index == j && !list->value && ft_strcmp(list->name, "_"))
				(void) (write(1, "declare -x ", 11) && write(1, list->name, ft_strlen(list->name))
					&& write(1, "\n", 1));
			list = list->next;
		}
	}
}

int	check_identifier(char *str, int *append)
{
	int	i;

	i = 1;
	*append = 0;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			*append = 1;
		else if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	b_export(t_lenv *env, char **argv)
{
	int		i;
	int		exit_s;
	char	*key;
	int		append;

	exit_s = 0;
	i = 1;
	if (!argv[1])
		return (dump_list(env), 0);
	while (argv[i])
	{
		if (check_identifier(argv[i], &append) == 0)
			exit_s = dump_err(argv[i]);
		else
		{
			key = get_name(env->session, argv[i]);
			if (append)
				append_env(env->session, env, key, get_value(env->session, argv[i]));
			else
				add_env(env->session, env, key, get_value(env->session, argv[i]));
		}
		i++;
	}
	return (exit_s);
}
