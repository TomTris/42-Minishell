CC				= cc 
CFLAGS			= -Wall -Werror -Wextra
HDR_FLAGS		= -I./libft -I./src
LFLAGS			= -Llibft -lreadline
RM				= rm -rf
PROMPT_SRC		= prompt/minishell.c
BLTIN_FILES		= exit cd exec pwd
BLTIN_SRC		=  $(patsubst %, builtin/%.c, $(BLTIN_FILES))
UTILS_SRC		= utils/utils.c
SRC				= $(PROMPT_SRC) $(BLTIN_SRC) $(UTILS_SRC)
TEST_SRC		= minishell.c
OBJS			= $(patsubst %.c, ./src/%.o, $(SRC))
TEST_PATH		= ./src/test
TEST_OBJS		= $(patsubst %.c, $(TEST_PATH)/%.o, $(TEST_SRC))
LIBFT			= libft/libft.a
NAME			= minishell

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HDR_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(HDR_FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

# test:  $(OBJS) $(TEST_OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) $(LFLAGS) $(TEST_FLAGS) -o $(TEST_PATH)/$(NAME) $(TEST_OBJS) $(LIBFT) && ./$(TEST_PATH)/$(NAME)

test:  $(NAME)
	./minishell

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