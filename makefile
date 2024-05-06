NAME = minishell
CFLAGS = -lreadline
SRC = main.c
OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)

re: fclean all