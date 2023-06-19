NAME := minishell
LIBFT := libft.a
FLAGS := -Wall -Wextra -lreadline -I libft -I srcs/tokenizer -g #TODO: remove -g & add -Werror

SRCS := $(addprefix srcs/,\
	minishell.c \
	prompt.c \
	tokenizer/states.c \
	tokenizer/tokenizer.c \
	tokenizer/linked_list_getter.c \
	tokenizer/linked_list_setter.c \
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
