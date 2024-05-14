CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = mini
LIBFT_DIR = ../libft
LIBFT_A = ../libft/libft.a
SRC = 	mini0.c 				sub_mini0.c				mini_unit0.c		\
		ft_isclosed.c 			syntax_check.c								\
		freq_used.c 			freq_used2.c 			ft_free.c			\
		dollar_handler.c		dollar_expand.c 		dollar_expand2.c	\
		ft_split_after_dollar_expansion.c 				ft_del_quote.c		\
		wildcard_expand.c		wildcard_expand2.c	\
		str_replace.c
OBJS = $(SRC:.c=.o)

fast: $(OBJS)
	cc -o $(NAME) $(OBJS) $(LIBFT_A)
	make clean
	./mini
all: $(NAME)

$(NAME): $(OBJS)
	make re -C $(LIBFT_DIR)
	cc -o $(NAME) $(OBJS) $(LIBFT_A)

clean:
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f  $(NAME)

re: fclean all clean

.PHONY: all clean fclean re bonus
