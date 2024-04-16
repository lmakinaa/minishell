/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/16 15:44:25 by ijaija           ###   ########.fr       */
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
	char				*value;
	int					is_operator;
	int					type;
	int					len;
	int					order;
	int					tokens_nbr;
	int					command;
}			t_token;

/*
* if op is not null, command will be, and the vice versa
*/
typedef struct s_tree_node
{
	struct s_mstoken	*operator;
	struct s_mstoken	**command;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}		t_tnode;

void		handle_prompt(t_memsession *heap_session, char *command);
t_token		**ms_lexer(t_memsession *session, char *command);
t_token		**tokenize_part_1(t_memsession *session, t_splitdata *splited_cmd);
void		print_tokens(t_token **tokens);

//	utilities

int			what_ops(char *str);
int			is_builtin(char *str);
int			get_token_type(char *str, int is_op);
int			is_redirector(t_token tok);
int			get_precedence(t_token *token);
void		void_return(void);

//	tree control

t_tnode		*create_node(t_memsession *session, int op,
				t_token *token, t_token ***tokens);
t_tnode		*build_tree(t_memsession *session, t_token ***tokens,
				int min_precedence);
void		print_tree(t_tnode *node, int space);
t_tnode		*nested_tree(t_memsession *session, t_token ***tokens);

#endif