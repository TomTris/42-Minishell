CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = parser
LIBFT_A = ../../libft/libft.a
SRC = 	ft_pre_check_input.c 		ft_frequent_used_func.c \
		ft_parenthesis_check_uniq.c ft_parenthesis_check_uniq2.c\
		ft_sign_check_empty.c
OBJS = $(SRC:.c=.o)

fast: $(OBJS)
	cc -o $(NAME) $(OBJS) $(LIBFT_A)
all: $(NAME)

$(NAME): $(OBJS)
	make re -C ../../libft
	cc -o $(NAME) $(OBJS) $(LIBFT_A)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f  $(NAME) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re bonus
