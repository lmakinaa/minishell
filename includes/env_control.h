#ifndef ENV_CONTROL_H
# define ENV_CONTROL_H

#include <stdlib.h>
#include <stdio.h>

// struct s_node t_node;
typedef struct	s_env_var{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}				t_env;

typedef struct	s_list{
	t_env	*head;
	t_env	*tail;
	int		exit_status;
}				t_lenv;

t_lenv	*envs_init(t_memsession *session, char **envp);
t_env 	*create_env(t_memsession *session, t_lenv *env, char *name, char *value);
void 	add_env(t_memsession *session, t_lenv *envs, char *name, char *value);
void 	remove_env(t_memsession *session, t_lenv *envs, char *name);
char	*get_env(t_lenv *env, char *name);
void 	envs_display(t_lenv *list);

#endif