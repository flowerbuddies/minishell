NAME := minishell
LIBFT := libft.a
BREW := $(shell brew --prefix)
INCS := -I $(BREW)/opt/readline/include -I libft -I srcs -I srcs/tokenizer -I srcs/env_var -I srcs/syntax_checker -I srcs/tree_constructor -I srcs/prompt -I srcs/executor -I srcs/builtin -I srcs/signals
LINK := -L $(BREW)/opt/readline/lib -lreadline
FLAGS := -Wall -Werror -Wextra $(LINK) $(INCS) -Ofast
DEBUG := -Wno-error -g -fsanitize=address,undefined -O0


SRCS := $(addprefix srcs/,\
	prompt/prompt.c \
	tokenizer/states/command.c \
	tokenizer/states/default.c \
	tokenizer/states/env_var.c \
	tokenizer/states/raw_string.c \
	tokenizer/states/string.c \
	tokenizer/linked_list/getter.c \
	tokenizer/linked_list/setter.c \
	tokenizer/tokenizer.c \
	env_var/env_var.c \
	env_var/path.c \
	env_var/linked_list/setter.c \
	env_var/linked_list/getter.c \
	tokenizer/post_process/evaluate_env_vars.c \
	tokenizer/post_process/concat_strings.c \
	tokenizer/post_process/delete_spaces.c \
	tokenizer/post_process/heredoc.c \
	syntax_checker/syntax_checker.c \
	tree_constructor/tree_constructor.c \
	executor/executor.c \
	executor/redirection.c \
	executor/argv_envp.c \
	executor/path.c \
	builtin/builtin.c \
	builtin/echo_cd_pwd.c \
	builtin/unset_env.c \
	builtin/export.c \
	signals/signals.c \
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
	@mv libft/$(LIBFT) .

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
