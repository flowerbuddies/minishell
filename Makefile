NAME := minishell
LIBFT := libft.a
FLAGS := -Wall -Wextra -Werror -lreadline -I libft -g #TODO: remove -g

SRCS := $(addprefix srcs/,\
	minishell.c \
	prompt.c \
)

.PHONY: all bonus clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft
	@mv libft/libft.a .

$(NAME):
	@echo "Compiling $(NAME)..."
	@cc $(FLAGS) $(LIBFT) $(SRCS) -o $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all
