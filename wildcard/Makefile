CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = a.out
LIBFT_H = ../libft
LIBFT_A = ../libft/libft.a
SRC = 	wildcard_expand.c dollar_expand.c
OBJS = $(SRC:.c=.o)

fast: $(OBJS)
	cc -o $(NAME) $(OBJS) $(LIBFT_A)
	make clean
	./($NAME)
all: $(NAME)

$(NAME): $(OBJS)
	make re -C $(LIBFT_H)
	cc -o $(NAME) $(OBJS) $(LIBFT_A)

clean:
	rm -f $(OBJS)

fclean:
	make clean -C $(LIBFT_H)
	rm -f  $(NAME) $(LIBFT_A)

re: fclean all clean

.PHONY: all clean fclean re bonus
