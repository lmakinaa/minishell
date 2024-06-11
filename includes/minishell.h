/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/06/09 18:01:22 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "./allocation_manager.h"
# include "./utils.h"
# include "./env_control.h"

# define SEPERATORS " \t\n"
# define BUFFER_SIZE 10
# define SYNTAX_ERR "near unexpected token"
# define SYNTAX_ERR_LEN 21
# define THROW_PERROR 2

# define LEFT_C 0
# define RIGHT_C 1

// Token types
// todo: change this shit into enum.. or not
# define T_UNKNOWN -1
# define T_APPEND_REDIR 1
# define T_PARENTHESIS_COMMAND 2
# define T_WORD 4
# define T_PIPE 7
# define T_VAR 8
# define T_OR 10
# define T_AND 11
# define T_HERDOC 13
# define T_INPUT_REDIRECTOR 14
# define T_OUT_REDIR 15
# define T_OUTPUT_FILE 16
# define T_INPUT_FILE 17
# define T_STD_INPUT 18

extern int	g_sig;

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
	t_lenv				*env;
	t_memsession		*session;
}		t_tnode;

// The final parsing part struct
typedef struct s_mscommand
{
	char				*path;
	char				**args;
	int					argc;
	char				**output_files;
	char				*output_redir_type;
	char				*input_file;
	int					std_input;
	t_lenv				*env;
	t_memsession		*session;
}			t_command;

//	execution
int			execute_command(t_memsession *session, t_lenv *env,
				t_token **tokens, int pip);
int			execute_tree(t_memsession *session, t_lenv *env,
				t_tnode *root, int pip);
int			reset_fds(int backup_fds[], int pip);
int			out_redirect(char **out, char *types);
int			in_redirect(char *input_file);
char		**generate_env_array(t_memsession *session, t_lenv *env);

//	builtins
int			b_export(t_lenv *env, char **argv);
int			b_echo(char **args);
int			b_pwd(void);
int			b_cd(t_command *command);
int			b_env(t_command *command);
int			b_unset(t_command *command);
int			b_exit(t_command *cmd, int b_f[]);

//	parse
void		handle_prompt(t_memsession *heap_session, t_lenv *env,
				char *command);
t_token		**tokenization(t_memsession *session, t_splitdata *splited_cmd);
t_token		**advanced_split(t_memsession *session, char *str, char *seps);
int			expander(t_memsession *session, t_lenv *env, t_token **cmd);
t_command	*parse_cmd(t_memsession *session, t_lenv *env,
				t_token **cmd, int i);
int			get_path(t_command *command);
t_command	*expand_n_generate_cmd(t_memsession *session, t_lenv *env,
				t_token **node);

//	utilities
int			check_identifier(char *str, int *append);
int			what_ops(char *str);
int			is_builtin(char *str);
int			get_token_type(char *str);
int			is_redirector(t_token tok);
int			get_precedence(t_token *token);
void		void_return(void);
int			is_word(t_token	*tok);
void		throw_error(char *error, char *arg, int len, int type);
int			are_quotes_closed(char *s);
int			are_parenthesis_closed(char *s);
char		*z_strdup(t_memsession *session, char **str, char *seps);
t_lenv		*ft_initialise(t_memsession **session1, t_memsession **session2,
				char **argv, char **envp);
void		end_sessions(t_memsession **s1, t_memsession **s2);
int			is_sep(char c, char *seps);
char		*expand_2(t_memsession *session, char *str);
int			handle_heredoc(t_memsession *session, t_token *tok);
char		*no_quotes(t_memsession *session, char *str, int flag);
int			tokenize_part2(t_token **cmd);
//void 		print_command_elements(t_command *command);
char		*expand_wildcard(t_memsession *session, char *str);
char		*get_exit_status(t_memsession *session, t_lenv *env);
int			is_identif(char c);
int			s_s(t_lenv *env, int status);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
void		sig_handle(int num);
int			extract_exit_status(int status);
char		**append_arg(t_memsession *session, char **args,
				char *value, int cmd);
char		**append_arr(t_memsession *session, char **arr1,
				char **arr2, int size);
void		reset_terminal(t_lenv *p_env);
void		set_es(t_lenv *env_p, int status);

//	tree control
t_tnode		*create_node(t_memsession *session, int op,
				t_token *token, t_token ***tokens);
t_tnode		*build_tree(t_memsession *session, t_token ***tokens,
				int min_precedence);
//void		print_tree(t_tnode *node, int space);
t_tnode		*nested_tree(t_memsession *session, t_token ***tokens);

#endif