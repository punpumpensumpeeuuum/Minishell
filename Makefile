NAME = minishell

SRCS = main.c paths.c utils.c moreutils.c quotes.c heredoc.c heredoc1.c heredoc_utils.c \
		signals.c free.c parsing.c evenmoreutils.c execution.c utils_again.c execution1.c execution2.c \
		free1.c pipes_redir.c antimalucos.c paodelosplit.c

BUILT = echo_builtin.c echo_builtin1.c env_builtin.c env_builtin1.c exit_builtin.c \
		cd_builtin.c cd_builtin1.c export_builtin.c export_builtin1.c export_utils.c \
		unset_builtin.c

GNL = get_next_line_utils.c get_next_line.c

CC = cc

CFLAGS = -Wall -Werror -Wextra  #-fsanitize=address

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
			clear
			@./minishell

va: $(NAME) clean
		@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no --suppressions="supp.supp" ./minishell

re:	fclean $(NAME)
		@echo "makou outra vez"