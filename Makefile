CC=cc
CFLAGS=-Wextra -Werror -Wall
NAME=minishell

# Minishell pack
SRC_DIR=./srcs
# SRC_C=
SRC_O=$(patsubst %.c, %.o, $(SRC_C))

# Allocation manager pack
ALLOC_MANAGER_DIR=$(SRC_DIR)/allocation_manager
ALLOC_MANAGER_C=$(ALLOC_MANAGER_DIR)/exit_on_error.c $(ALLOC_MANAGER_DIR)/reset_session.c $(ALLOC_MANAGER_DIR)/add_to_session.c\
	$(ALLOC_MANAGER_DIR)/session_destroy.c $(ALLOC_MANAGER_DIR)/session_init.c $(ALLOC_MANAGER_DIR)/session_malloc.c
ALLOC_MANAGER_O=$(patsubst %.c, %.o, $(ALLOC_MANAGER_C))

# Utils pack
UTILS_DIR=$(SRC_DIR)/utils
UTILS_C=$(UTILS_DIR)/ft_strcmp.c
UTILS_O=$(patsubst %.c, %.o, $(UTILS_C))

# Includes
INCLUDES=./includes
UTILS_H=$(INCLUDES)/utils.h
ALLOC_MANAGER_H=$(INCLUDES)/allocation_manager.h
MINISHELL_H=$(INCLUDES)/minishell.h

all: $(NAME)

$(NAME): $(SRC_O) $(ALLOC_MANAGER_O) $(UTILS_O) $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $^ -lreadline -o $@

$(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(ALLOC_MANAGER_DIR)/%.o : $(ALLOC_MANAGER_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_DIR)/%.o : $(UTILS_DIR)/%.c $(MINISHELL_H) $(ALLOC_MANAGER_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(UTILS_O) $(ALLOC_MANAGER_O) $(SRC_O)

fclean: clean
	rm -f $(NAME)

.PHONY: clean fclean
