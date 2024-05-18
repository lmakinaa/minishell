CC=cc
CFLAGS=-g -fsanitize=address
NAME=minishell
SRC_DIR=./srcs

# Parse files pack
PARSE_DIR=$(SRC_DIR)/parse
PARSE_C=$(PARSE_DIR)/handle_prompt.c $(PARSE_DIR)/print_tokens.c $(PARSE_DIR)/utilities.c $(PARSE_DIR)/utilities_2.c $(PARSE_DIR)/utilities_3.c\
	$(PARSE_DIR)/expander.c $(PARSE_DIR)/env_control.c $(PARSE_DIR)/parse_cmd.c $(PARSE_DIR)/handle_wildcard.c $(PARSE_DIR)/get_path.c\
	$(PARSE_DIR)/advanced_split.c $(PARSE_DIR)/shave_parenthesis.c $(PARSE_DIR)/handle_heredoc.c $(PARSE_DIR)/sort_env.c \
	$(PARSE_DIR)/build_tree.c $(PARSE_DIR)/print_tree.c $(PARSE_DIR)/utilities_4.c $(PARSE_DIR)/env_control_2.c
PARSE_O=$(patsubst %.c, %.o, $(PARSE_C))

# Execution pack
EXEC_DIR=$(SRC_DIR)/execution
EXEC_C=$(EXEC_DIR)/execute_tree.c $(EXEC_DIR)/execute_command.c $(EXEC_DIR)/redirect.c $(EXEC_DIR)/utilities.c
EXEC_O=$(patsubst %.c, %.o, $(EXEC_C))

# Builtins pack
BUILTINS_DIR=$(SRC_DIR)/builtins
BUILTINS_C=$(BUILTINS_DIR)/echo.c $(BUILTINS_DIR)/export.c $(BUILTINS_DIR)/pwd.c $(BUILTINS_DIR)/cd.c $(BUILTINS_DIR)/env.c $(BUILTINS_DIR)/unset.c\
	$(BUILTINS_DIR)/exit.c
BUILTINS_O=$(patsubst %.c, %.o, $(BUILTINS_C))

# Allocation manager pack
ALLOC_MANAGER_DIR=$(SRC_DIR)/allocation_manager
ALLOC_MANAGER_C=$(ALLOC_MANAGER_DIR)/exit_on_error.c $(ALLOC_MANAGER_DIR)/reset_session.c $(ALLOC_MANAGER_DIR)/add_to_session.c\
	$(ALLOC_MANAGER_DIR)/session_destroy.c $(ALLOC_MANAGER_DIR)/session_init.c $(ALLOC_MANAGER_DIR)/session_malloc.c $(ALLOC_MANAGER_DIR)/del_from_session.c
ALLOC_MANAGER_O=$(patsubst %.c, %.o, $(ALLOC_MANAGER_C))

# Utils pack
UTILS_DIR=$(SRC_DIR)/utils
UTILS_C=$(UTILS_DIR)/ft_strcmp.c $(UTILS_DIR)/ft_strlen.c $(UTILS_DIR)/ft_strchr.c $(UTILS_DIR)/ft_count_words.c\
	$(UTILS_DIR)/ft_strncmp.c $(UTILS_DIR)/ft_strncpy.c $(UTILS_DIR)/strdup_versions.c $(UTILS_DIR)/ft_strnstr.c\
	$(UTILS_DIR)/ft_strdup.c $(UTILS_DIR)/ft_strjoin.c $(UTILS_DIR)/ft_split.c $(UTILS_DIR)/ft_isalnum.c
UTILS_O=$(patsubst %.c, %.o, $(UTILS_C))


# Includes
INCLUDES=./includes
UTILS_H=$(INCLUDES)/utils.h
ALLOC_MANAGER_H=$(INCLUDES)/allocation_manager.h
MINISHELL_H=$(INCLUDES)/minishell.h

all: $(NAME)

$(NAME): $(PARSE_O) $(ALLOC_MANAGER_O) $(UTILS_O) $(TREE_CONTROL_O) $(EXEC_O) $(BUILTINS_O) $(SRC_DIR)/main.c
	@$(CC) $(CFLAGS) $^ -I/Users/ijaija/.brew/opt/readline/include -lreadline -L/Users/ijaija/.brew/opt/readline/lib/ -o $@
	@echo "\033[0;32mDone making minishell!\033[0m"

$(PARSE_DIR)/%.o : $(PARSE_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	@$(CC) $(CFLAGS) -c $< -I/Users/ijaija/.brew/opt/readline/include -o $@

$(EXEC_DIR)/%.o : $(EXEC_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	@$(CC) $(CFLAGS) -c $< -I/Users/ijaija/.brew/opt/readline/include -o $@

$(BUILTINS_DIR)/%.o : $(BUILTINS_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	@$(CC) $(CFLAGS) -c $< -I/Users/ijaija/.brew/opt/readline/include -o $@

$(ALLOC_MANAGER_DIR)/%.o : $(ALLOC_MANAGER_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	@$(CC) $(CFLAGS) -c $< -I/Users/ijaija/.brew/opt/readline/include -o $@

$(UTILS_DIR)/%.o : $(UTILS_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	@$(CC) $(CFLAGS) -c $< -I/Users/ijaija/.brew/opt/readline/include -o $@

$(TREE_CONTROL_DIR)/%.o : $(TREE_CONTROL_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	@$(CC) $(CFLAGS) -c $< -I/Users/ijaija/.brew/opt/readline/include -o $@

clean:
	@rm -f $(UTILS_O) $(ALLOC_MANAGER_O) $(PARSE_O) $(EXEC_O) $(BUILTINS_O) $(TREE_CONTROL_O)
	@echo "\033[0;31mDone removing object files.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31mDone removing inishell program.\033[0m"

re: fclean all

.PHONY: clean fclean
