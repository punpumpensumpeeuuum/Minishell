NAME = libft.a

SRCS =	ft_putchar_fd.c \
	ft_putstr_fd.c \

OBJ = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
			ar rcs $(NAME) $(OBJ)

clean:
			$(RM) $(OBJ)

fclean:	clean
			$(RM) $(NAME)

re:	fclean $(NAME)