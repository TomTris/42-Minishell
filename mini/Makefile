CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = mini
LIBFT_H = ../libft
LIBFT_A = ../libft/libft.a
SRC = 	mini0.c 			sub_mini0.c			mini_unit0.c		\
		ft_isclosed.c 		syntax_check.c							\
		freq_used.c 		freq_used2.c 		ft_free.c			\
		dollar_expand.c 	dollar_expand2.c	wildcard_expand.c 		wildcard_expand2.c\
		str_replace.c
OBJS = $(SRC:.c=.o)

fast: $(OBJS)
	cc -o $(NAME) $(OBJS) $(LIBFT_A)
	make clean
# ./mini
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
