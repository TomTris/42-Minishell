CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = mini
LIBFT_H = ../libft
LIBFT_A = ../libft/libft.a
SRC = 	mini0.c sub_mini0.c mini_unit0.c\
		freq_used.c ft_pre_check_syntax.c ft_free.c
OBJS = $(SRC:.c=.o)

fast: $(OBJS)
	cc -o $(NAME) $(OBJS) $(LIBFT_A)
all: $(NAME)

$(NAME): $(OBJS)
	make re -C $(LIBFT_H)
	cc -o $(NAME) $(OBJS) $(LIBFT_A)

clean:
	rm -f $(OBJS)

fclean:
	make clean -C $(LIBFT_H)
	rm -f  $(NAME) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re bonus
