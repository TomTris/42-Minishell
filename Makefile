CC				= cc 
CFLAGS			= -Wall -Werror -Wextra -I./libft
LIBFT_FLAGS		= -Llibft
TEST_FLAGS		= -I./libft -I./src/prompt
LFLAGS			= $(LIBFT_FLAGS)
RM				= rm -rf
SRC				= prompt/minishell.c
# TEST_SRC		= test/minishell.c TODO: make tests
OBJS			= $(patsubst %.c, ./src/%.o, $(SRC))
LIBFT			= libft/libft.a
NAME			= minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

# TODO: test: $(NAME)

libft: $(LIBFT)

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean bonus re fclean