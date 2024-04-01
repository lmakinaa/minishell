/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/01 23:48:52 by ijaija           ###   ########.fr       */
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

# define T_REDIRECTORS 1
# define T_EXECUTABLE 2
# define T_BUILTIN 3
# define T_ARG 4
# define T_FLAG 5
# define T_S_QUOTES 6
# define T_PIPE 7
# define T_VAR 8
# define T_AUTOMATIC_VAR 9
# define T_OR 10
# define T_AND 11
# define T_D_QUOTES 12

/*
* A struct used for identifying the command tokens. Its members are :
*	- data : string that hold the token value
*	- type : an int indicating its type (see tokens types in minishell.h)
*/
typedef struct s_mstoken
{
	char	*value;
	int		type;
	int		len;
	int		order;
	int		tokens_nbr;
}			t_token;

void		handle_command(t_memsession *heap_session, char *command);
t_token		*ms_lexer(t_memsession *session, char *command);
int			get_token_type(char *str, int order);
void		print_tokens(t_token *tokens);

#endif