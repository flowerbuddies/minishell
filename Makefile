NAME := minishell
LIBFT := libft.a
INCS := -I libft -I srcs -I srcs/tokenizer -I srcs/env_var
FLAGS := -Wall -Werror -Wextra -lreadline $(INCS) -Ofast
DEBUG := -Wno-error -g -fsanitize=address,undefined -O0

SRCS := $(addprefix srcs/,\
	prompt.c \
	tokenizer/states/command.c \
	tokenizer/states/default.c \
	tokenizer/states/env_var.c \
	tokenizer/states/raw_string.c \
	tokenizer/states/string.c \
	tokenizer/linked_list/getter.c \
	tokenizer/linked_list/setter.c \
	tokenizer/tokenizer.c \
	tokenizer/concatenate/concat_strings.c \
	tokenizer/concatenate/concat_spaces.c \
	env_var/env_var.c \
	env_var/linked_list/setter.c \
	env_var/linked_list/getter.c \
)

TESTS_SRCS := $(addprefix tests/,\
	munit/munit.c \
	test.c \
	test_tokenizer.c \
)

.PHONY: all bonus clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft
	@mv libft/libft.a .

$(NAME):
	@echo "Compiling $(NAME)..."
	@cc $(FLAGS) $(LIBFT) $(SRCS) srcs/minishell.c -o $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: fclean
	@echo "Compiling debug..."
	@cc $(FLAGS) $(DEBUG) $(LIBFT) $(SRCS) srcs/minishell.c -o $(NAME)
	@./$(NAME)

debug-leaks:
	@echo "Compiling debug using leaks..."
	@cc $(FLAGS) $(DEBUG) -fno-sanitize=all $(LIBFT) $(SRCS) srcs/minishell.c -o $(NAME)
	@leaks -q --atExit -- ./$(NAME)

test: re
	@echo "Compiling tests..."
	@cc $(FLAGS) $(DEBUG) $(LIBFT) $(SRCS) $(TESTS_SRCS) -o test
	@./test
	@rm -f test

test-leaks:
	@echo "Compiling tests using leaks..."
	@cc $(FLAGS) $(DEBUG) -fno-sanitize=all $(LIBFT) $(SRCS) $(TESTS_SRCS) -o test
	@leaks -q --atExit -- ./test
	@rm -f test
