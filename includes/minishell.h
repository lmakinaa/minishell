/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaija <ijaija@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:46:44 by ijaija            #+#    #+#             */
/*   Updated: 2024/03/14 14:50:19 by ijaija           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h> // to remove
# include "./allocation_manager.h"
# include "./utils.h"

# define PROMPT_TEXT "\033[0;32m$> \033[0m"

// Token types

# define T_OPERATOR 1
# define T_EXECUTABLE 2
# define T_BUILTIN 3
# define T_ARG 4
# define T_FLAG 5

typedef struct s_mstoken
{
	char	*data;
	int		type;
}			t_token;

void		handle_command(t_memsession *heap_session, char *command);

#endif