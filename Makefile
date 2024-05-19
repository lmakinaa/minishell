CC=cc
CFLAGS=-g
NAME=minishell
RDLINE_PATH=/Users/ijaija/.brew/opt/readline

# Parse files pack
PARSE =	srcs/parse/advanced_split.c\
		srcs/parse/build_tree.c\
		srcs/parse/env_control.c\
		srcs/parse/env_control_2.c\
		srcs/parse/expander.c\
		srcs/parse/get_path.c\
		srcs/parse/handle_heredoc.c\
		srcs/parse/handle_prompt.c\
		srcs/parse/handle_wildcard.c\
		srcs/parse/parse_cmd.c\
		srcs/parse/print_tokens.c\
		srcs/parse/print_tree.c\
		srcs/parse/shave_parenthesis.c\
		srcs/parse/sort_env.c\
		srcs/parse/utilities.c\
		srcs/parse/utilities_2.c\
		srcs/parse/utilities_3.c\
		srcs/parse/utilities_4.c

# Execution pack
EXEC =	srcs/execution/execute_command.c\
		srcs/execution/execute_tree.c\
		srcs/execution/redirect.c\
		srcs/execution/utilities.c

# Builtins pack
BUILTINS = 	srcs/builtins/cd.c\
			srcs/builtins/echo.c\
			srcs/builtins/env.c\
			srcs/builtins/exit.c\
			srcs/builtins/export.c\
			srcs/builtins/pwd.c\
			srcs/builtins/unset.c

# Allocation manager pack
ALLOC_MANAGER = srcs/allocation_manager/add_to_session.c\
				srcs/allocation_manager/del_from_session.c\
				srcs/allocation_manager/exit_on_error.c\
				srcs/allocation_manager/reset_session.c\
				srcs/allocation_manager/session_destroy.c\
				srcs/allocation_manager/session_init.c\
				srcs/allocation_manager/session_malloc.c

# Utils pack
UTILS = srcs/utils/ft_count_words.c\
		srcs/utils/ft_isalnum.c\
		srcs/utils/ft_split.c\
		srcs/utils/ft_strchr.c\
		srcs/utils/ft_strcmp.c\
		srcs/utils/ft_strdup.c\
		srcs/utils/ft_strjoin.c\
		srcs/utils/ft_strlen.c\
		srcs/utils/ft_strncmp.c\
		srcs/utils/ft_strncpy.c\
		srcs/utils/ft_strnstr.c\
		srcs/utils/strdup_versions.c

SRCS = 	$(PARSE)\
		$(EXEC)\
		$(BUILTINS)\
		$(ALLOC_MANAGER)\
		$(UTILS)\
		srcs/main.c

OBJS=$(SRCS:.c=.o)

# Includes
INCLUDES =	includes/allocation_manager.h\
			includes/env_control.h\
			includes/minishell.h\
			includes/utils.h

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -lreadline -L$(RDLINE_PATH)/lib -o $@
	@echo "\033[0;32mDone making minishell!\033[0m"

bonus: $(NAME)

%.o : %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -I$(RDLINE_PATH)/include -o $@

clean:
	@rm -f $(OBJS)
	@echo "\033[0;31mDone removing object files.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31mDone removing inishell program.\033[0m"

re: fclean all

.PHONY: clean
