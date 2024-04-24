CC=cc
CFLAGS=-Wextra -Werror -Wall
NAME=minishell

# Minishell src files pack
SRC_DIR=./srcs
SRC_C=$(SRC_DIR)/handle_prompt.c $(SRC_DIR)/print_tokens.c $(SRC_DIR)/utilities.c $(SRC_DIR)/utilities_2.c $(SRC_DIR)/utilities_3.c\
	$(SRC_DIR)/syntax_analyze.c $(SRC_DIR)/expander.c $(SRC_DIR)/env_control.c $(SRC_DIR)/parse_cmd.c $(SRC_DIR)/handle_wildcard.c
SRC_O=$(patsubst %.c, %.o, $(SRC_C))

# Allocation manager pack
ALLOC_MANAGER_DIR=$(SRC_DIR)/allocation_manager
ALLOC_MANAGER_C=$(ALLOC_MANAGER_DIR)/exit_on_error.c $(ALLOC_MANAGER_DIR)/reset_session.c $(ALLOC_MANAGER_DIR)/add_to_session.c\
	$(ALLOC_MANAGER_DIR)/session_destroy.c $(ALLOC_MANAGER_DIR)/session_init.c $(ALLOC_MANAGER_DIR)/session_malloc.c $(ALLOC_MANAGER_DIR)/del_from_session.c
ALLOC_MANAGER_O=$(patsubst %.c, %.o, $(ALLOC_MANAGER_C))

# Utils pack
UTILS_DIR=$(SRC_DIR)/utils
UTILS_C=$(UTILS_DIR)/ft_strcmp.c $(UTILS_DIR)/advanced_split.c $(UTILS_DIR)/ft_strlen.c $(UTILS_DIR)/ft_strchr.c $(UTILS_DIR)/ft_count_words.c\
	$(UTILS_DIR)/ft_strncmp.c $(UTILS_DIR)/ft_strncpy.c $(UTILS_DIR)/shave_parenthesis.c $(UTILS_DIR)/strdup_versions.c $(UTILS_DIR)/gnl.c\
	$(UTILS_DIR)/ft_strdup.c $(UTILS_DIR)/ft_strjoin.c
UTILS_O=$(patsubst %.c, %.o, $(UTILS_C))

# tree control pack
TREE_CONTROL_DIR=$(SRC_DIR)/tree_control
TREE_CONTROL_C=$(TREE_CONTROL_DIR)/create_node.c $(TREE_CONTROL_DIR)/build_tree.c $(TREE_CONTROL_DIR)/print_tree.c
TREE_CONTROL_O=$(patsubst %.c, %.o, $(TREE_CONTROL_C))

# Includes
INCLUDES=./includes
UTILS_H=$(INCLUDES)/utils.h
ALLOC_MANAGER_H=$(INCLUDES)/allocation_manager.h
MINISHELL_H=$(INCLUDES)/minishell.h

all: $(NAME)

$(NAME): $(SRC_O) $(ALLOC_MANAGER_O) $(UTILS_O) $(TREE_CONTROL_O) $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $^ -I/Users/ijaija/.brew/opt/readline/include -lreadline -L/Users/ijaija/.brew/opt/readline/lib/ -o $@

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(ALLOC_MANAGER_DIR)/%.o : $(ALLOC_MANAGER_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_DIR)/%.o : $(UTILS_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(TREE_CONTROL_DIR)/%.o : $(TREE_CONTROL_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(UTILS_O) $(ALLOC_MANAGER_O) $(SRC_O) $(TREE_CONTROL_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean
