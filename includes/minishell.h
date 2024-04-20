/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/04/20 20:05:27 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h> // to remove
# include <readline/readline.h>
# include <readline/history.h>
# include "./allocation_manager.h"
# include "./utils.h"
# include "./env_control.h"

# define PROMPT_TEXT "\033[0;32m$> \033[0m"
# define SEPERATORS " \t\n"
# define BUFFER_SIZE 10

// Token types

# define T_UNKNOWN -1
# define T_APPEND_REDIR 1
# define T_PARENTHESIS_COMMAND 2
# define T_WORD 4
# define T_PIPE 7
# define T_VAR 8
# define T_AUTOMATIC_VAR 9
# define T_OR 10
# define T_AND 11
# define T_HERDOC 13
# define T_INPUT_REDIRECTOR 14
# define T_OUT_REDIR 15


# define T_BUILTIN 3
# define T_EXECUTABLE 5
# define T_OUTPUT_FILE 16
# define T_INPUT_FILE 17
# define T_STD_INPUT 18
# define T_STD_INPUT 18
# define T_ARG 19

// These 2 structs are for the initial parsing part

typedef struct s_mstoken
{
	char				*value;
	int					type;
	int					tokens_nbr;
	int					command;
}			t_token;

typedef struct s_tree_node
{
	struct s_mstoken	*operator;
	struct s_mstoken	**command;
	struct s_mscommand	*parsed_cmd;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}		t_tnode;

// The final parsing part struct

typedef struct s_mscommand
{
	char				*exec;
	char				*builtin;
	char				**output_files; // after parsing the redirectors in order
	int					output_redir_type; // is it replace (>) or append (>>), don't mind if output_files == NULL
	char				**args;
	char				*std_input;	// the here-doc entry (<<)
	char				*input_file; // after parsing the input redir (<)
	int					elements_count; // the number of command elements
}			t_command;

void		handle_prompt(t_memsession *heap_session, char *command);
t_token		**tokenization(t_memsession *session, t_splitdata *splited_cmd);
void		print_tokens(t_token **tokens);
t_token		**advanced_split(t_memsession *session, char *str, char *seps);
int			expander(t_memsession *session, t_token **cmd);

//	utilities

int			what_ops(char *str);
int			is_builtin(char *str);
int			get_token_type(char *str);
int			is_redirector(t_token tok);
int			get_precedence(t_token *token);
void		void_return(void);
int			is_word(t_token	*tok);
void		syntax_error(char *error, int len);
int			are_quotes_closed(char *s);
int			are_parenthesis_closed(char *s);
char		*z_strdup(t_memsession *session, char **str, char *seps);

//	tree control

t_tnode		*create_node(t_memsession *session, int op,
				t_token *token, t_token ***tokens);
t_tnode		*build_tree(t_memsession *session, t_token ***tokens,
				int min_precedence);
void		print_tree(t_tnode *node, int space);
t_tnode		*nested_tree(t_memsession *session, t_token ***tokens);
int			more_parse(t_memsession *session, t_tnode *root);

#endif