CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = mini
LIBFT_DIR = ../libft
LIBFT_A = ../libft/libft.a
SRC = 	\
		mini_mini.c				mini_sub_mini.c			mini_mini_unit.c													\
		syntax_precheck.c		syntax_check.c																				\
		expansion_0.c			expansion_dollar1.c		expansion_dollar2.c		expansion_dollar3.c							\
		expansion_dollar4.c		expansion_wildcard1.c	expansion_wildcard2.c												\
		break_input.c			break_input2.c			break_input3.c			break_input4.c								\
		ft_free.c				ft_other1.c				ft_other2.c				ft_other3.c									\
		ft_clean1.c				ft_clean2.c

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
