NAME = minishell
CFLAGS = -lreadline
SRC = main.c
OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	make -C libft
	cc $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all