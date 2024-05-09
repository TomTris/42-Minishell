CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = parser
SRC = ft_pre_check_input.c ft_frequent_used_func.c ft_parenthesis_check.c
OBJS = $(SRC:.c=.o)

fast: $(OBJS)
	cc -o $(NAME) $(OBJS) ../libft/libft.a
all: $(NAME)

$(NAME): $(OBJS)
	make re -C ../libft
	cc -o $(NAME) $(OBJS) ../libft/libft.a

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f  $(NAME) ../libft/libft.a

re: fclean all

.PHONY: all clean fclean re bonus
