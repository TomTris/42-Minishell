CC				= cc 
CFLAGS			= -Wall -Werror -Wextra -I./libft
LIBFT_FLAGS		= -Llibft
TEST_FLAGS		= -I./libft -I./src/prompt
LFLAGS			= $(LIBFT_FLAGS)
RM				= rm -rf
SRC				= prompt/minishell.c
TEST_SRC		= minishell.c
OBJS			= $(patsubst %.c, ./src/%.o, $(SRC))
TEST_PATH		= ./src/test
TEST_OBJS		= $(patsubst %.c, $(TEST_PATH)/%.o, $(TEST_SRC))
LIBFT			= libft/libft.a
NAME			= minishell

all: $(NAME)

src/test/%.o: src/test/%.c
	$(CC) $(TEST_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

test:  $(OBJS) $(TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(TEST_FLAGS) -o $(TEST_PATH)/$(NAME) $(TEST_OBJS) $(LIBFT) && ./$(TEST_PATH)/$(NAME)

libft: $(LIBFT)

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)
	rm -rf $(TEST_OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(TEST_PATH)/$(NAME)

re: fclean all

.PHONY: all clean bonus re fclean