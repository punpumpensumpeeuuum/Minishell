NAME = minishell

SRCS = main.c goodsplit.c executecmd.c paths.c utils.c moreutils.c quotes.c

BUILT = echo_builtin.c env_builtin.c exit_builtin.c export_builtin.c

GNL = get_next_line_utils.c get_next_line.c

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(addprefix get_next_line/,$(GNL))
		@make -s -C ft_printf
		@make -s -C libft
		@$(CC) -g $(CFLAGS) $(OBJ) $(addprefix builtins/,$(BUILT)) ft_printf/libftprintf.a libft/libft.a -o $(NAME) -lreadline

clean:
		@$(RM) $(OBJ)
		@make clean -s -C libft
		@make clean -s -C ft_printf

fclean:	clean
		@$(RM) $(NAME)
		@make fclean -s -C libft
		@make fclean -s -C ft_printf
		@echo "apagou"

so:	$(NAME) clean

re:	fclean $(NAME)
		@echo "makou outra vez"