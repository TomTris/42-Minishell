CC				= cc 
CFLAGS			= -Wall -Werror -Wextra
HDR_FLAGS		= -I./libft -I./src -I./src/shared
LFLAGS			= -Llibft -lreadline
RM				= rm -rf
PROMPT_SRC		= prompt/minishell.c
BUILTIN			= builtin_exec exit cd pwd env export echo
BLTIN_SRC		= $(patsubst %, builtin/%.c, $(BUILTIN))
ENV				= ft_env_changing ft_handle_env env env_utils utils
ENV_SRC			= $(patsubst %, shared/%.c, $(ENV))
SRC				= $(PROMPT_SRC) $(BLTIN_SRC) $(ENV_SRC)
TEST_SRC		= minishell.c
OBJS			= $(patsubst %.c, ./src/%.o, $(SRC))
LIBFT			= libft/libft.a
NAME			= minishell

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HDR_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(HDR_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) && ./minishell

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