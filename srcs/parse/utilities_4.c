/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:43:18 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/26 20:54:41 by ijaija           ###   ########.fr       */
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
	printf("Output Files:\n");
	if (command->output_files != NULL)
	{
		for (int i = 0; command->output_files[i] != NULL; i++)
			printf("%s\n", command->output_files[i]);
	}
	printf("Output Redirection Type: %d\n", command->output_redir_type);
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
				return (throw_error("near > or >>", 12, 1), -1);
			cmd[i + 1]->type = T_OUTPUT_FILE;
		}
		else if (cmd[i]->type == T_INPUT_REDIRECTOR)
		{
			if (!cmd[i + 1] || !is_word(cmd[i + 1]))
				return (throw_error("near <", 6, 1), -1);
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
