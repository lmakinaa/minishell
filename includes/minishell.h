/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/04 20:17:31 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // to remove
# include <readline/readline.h>
# include <readline/history.h>
# include "./allocation_manager.h"
# include "./utils.h"

# define PROMPT_TEXT "\033[0;32m$> \033[0m"
# define SEPERATORS " \t\n"

// Token types

# define T_UNKNOWN -1
# define T_APPEND_REDIRECTOR 1
# define T_PARENTHESIS_COMMAND 2
# define T_BUILTIN 3
# define T_WORD 4
# define T_PIPE 7
# define T_VAR 8
# define T_AUTOMATIC_VAR 9
# define T_OR 10
# define T_AND 11
# define T_HERDOC 13
# define T_INPUT_REDIRECTOR 14
# define T_OUTPUT_REDIRECTOR 15

/*
* A struct used for identifying the command tokens. Its members are :
*	- value : string that hold the token value
*	- operator : 0 if its not an operator and 1 if it is
*	- type : an int indicating its type (see tokens types in minishell.h)
*	- len
*	- order
*	- tokens_nbr
*	- commad : 1 if it is a part of a command
*/
typedef struct s_mstoken
{
	char	*value;
	int		is_operator;
	int		type;
	int		len;
	int		order;
	int		tokens_nbr;
	int		command;
}			t_token;

void		handle_prompt(t_memsession *heap_session, char *command);
t_token		*ms_lexer(t_memsession *session, char *command);
void		print_tokens(t_token *tokens);

#endif