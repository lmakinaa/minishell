/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:26:14 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/26 20:26:42 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

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

int	tokenize_part3(t_token **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i]->type == T_UNKNOWN)
			cmd[i]->type = T_ARG;
	return (0);
}

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

int	execute_tree(t_memsession *session, t_lenv *env, t_tnode *root)
{
	t_command	*command;

	if (!root)
		return (0);
	if (execute_tree(session, env, root->left) == -1)
		return (-1);
	if (execute_tree(session, env, root->right) == -1)
		return (-1);
	if (root->command)
	{
		if (tokenize_part2(root->command) == -1)
			return (-1);
		if (expander(session, env, root->command) == -1)
			return (-1);
		command = parse_cmd(session, env, root->command);
		print_command_elements(command);
	}
	return (0);
}
