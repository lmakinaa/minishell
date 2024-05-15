/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:43:18 by ijaija            #+#    #+#             */
/*   Updated: 2024/05/15 19:20:18 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void print_command_elements(t_command *command)
{
	char	buff[50];
	int     bytes_read;

	//printf("Command: %s\n", command->cmd);
	printf("Arguments:\n");
	if (command->args)
	{
		for (int i = 0; command->args[i] != NULL; i++)
			printf("%s\n", command->args[i]);
	}
	printf("Path: %s\n", command->path);
	printf("Output Files:\n");
	if (command->output_files != NULL)
	{
		for (int i = 0; command->output_files[i] != NULL; i++)
			printf("%s\n", command->output_files[i]);
	}
	//printf("Output Redirection Type: %s\n", command->output_redir_type);
	printf("Input File: %s\n", command->input_file);
	printf("Standard Input:\n");
	if (command->std_input == -1)
		return ;
	buff[0] = '\0';
	while ((bytes_read = read(command->std_input, buff, 49)) > 0)
    {
        buff[bytes_read] = '\0';
        printf("%s", buff);
    }
	//close(command->std_input);
}

void	sig_handle(int num)
{
	g_sig = num;
	if (num == SIGINT)
		write(1, "\n", 1);
}

// rl

/*
* it focuses on redirections
*/
int	tokenize_part2(t_token **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->type == T_OUT_REDIR || cmd[i]->type == T_APPEND_REDIR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (throw_error(SYNTAX_ERR, cmd[i]->value, 21, 1), -1);
			cmd[i + 1]->type = T_OUTPUT_FILE;
		}
		else if (cmd[i]->type == T_INPUT_REDIRECTOR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (throw_error(SYNTAX_ERR, "<", 21, 1), -1);
			cmd[i + 1]->type = T_INPUT_FILE;
		}
	}
	return (0);
}

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

char	*get_env(t_lenv *env, char *name)
{
	t_env	*f_env;

	if (!env->head)
		return (NULL);
	f_env = env->head;
	while (f_env)
	{
		if (!ft_strcmp(f_env->name, name))
			return (f_env->value);
		f_env = f_env->next;
	}
	return (NULL);
}

char	*get_exit_status(t_memsession *session, t_lenv *env)
{
	char		*res;
	int			code;
	int			i;
	
	res = session_malloc(session, 4 * sizeof(char), 0);
	code = env->exit_status;
	i = 0;
	while (code / 10)
		(1) && (code /= 10, i++);
	code = env->exit_status;
	res[i + 1] = '\0';
	while (code / 10)
	{
		res[i--] = (code % 10) + '0';
		code /= 10;
	}
	res[i] = (code % 10) + '0';
	return (res);
}

int	is_identif(char c)
{
	return (ft_isalpha(c) || c == '?' || c == '_'
		|| (c == '\'' || c == '"'));
}
