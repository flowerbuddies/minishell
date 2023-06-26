NAME := minishell
LIBFT := libft.a
FLAGS := -Wall -Werror -Wextra -lreadline -I libft -I srcs/tokenizer
DEBUG := -Wno-error -g -fsanitize=address,undefined

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
	tokenizer/concat_strings.c \
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
	@cc $(FLAGS) $(DEBUG) $(LIBFT) $(SRCS) srcs/minishell.c -o $(NAME) #TODO: rm DEBUG

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: re
	@echo "Compiling tests..."
	@cc $(FLAGS) $(DEBUG) $(LIBFT) $(SRCS) $(TESTS_SRCS) -o test
	@./test
	@rm -f test
