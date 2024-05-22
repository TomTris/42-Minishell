CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
NAME = mini
LIBFT_DIR = ../libft
LIBFT_A = ../libft/libft.a
SRC = 	\
		mini_mini.c				mini_sub_mini.c			mini_mini_unit.c		mini_mini_start.c							\
		syntax_precheck.c		syntax_check.c																				\
		expansion_0.c			expansion_dollar1.c		expansion_dollar2.c		expansion_dollar3.c							\
		expansion_dollar4.c		expansion_wildcard1.c	expansion_wildcard2.c												\
		break_input.c			break_input2.c			break_input3_heredoc.c	break_input4_heredoc.c						\
		break_input5_heredoc.c	break_input6_redi.c																			\
		ft_free.c				ft_other1.c				ft_other2.c				ft_other3.c									\
		ft_clean1.c				ft_clean2.c																					\
		execute_mini_unit_ft_execve.c 					execute_mini_unit_redi.c\
		execute_mini_unit.c								execute_mini.c\
		execute_sub_mini.c\
		ft_builtin_env.c\
		ft_builtin_unset.c\
		ft_builtin_export.c ft_builtin_export2.c ft_builtin_echo.c\
		ft_builtin_pwd.c ft_builtin_exit.c ft_builtin_add_rm.c\
		execute_sub_mini_env_underscore.c
OBJS = $(SRC:.c=.o)

fast: $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS)
	make clean
	./mini

all: $(NAME)

$(NAME): $(OBJS)
	make re -C $(LIBFT_DIR)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f  $(NAME)

re: fclean all clean

.PHONY: all clean fclean re bonus
