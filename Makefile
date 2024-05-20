CC				= cc 
CFLAGS			= -Wall -Werror -Wextra
HDR_FLAGS		= -I./libft -I./src -I./src/shared -I./mini
LFLAGS			= -Llibft -lreadline
RM				= rm -rf
PROMPT_SRC		= prompt/minishell.c
BUILTIN			= builtin_exec exit cd pwd env export echo unset utils
BLTIN_SRC		= $(patsubst %, builtin/%.c, $(BUILTIN))
ENV				= ft_env_changing ft_handle_env env env_utils utils
ENV_SRC			= $(patsubst %, shared/%.c, $(ENV))
MINI			= 			mini_mini				mini_sub_mini			mini_mini_unit								\
				syntax_precheck		syntax_check																				\
				expansion_0			expansion_dollar1		expansion_dollar2		expansion_dollar3							\
				expansion_dollar4		expansion_wildcard1	expansion_wildcard2												\
				break_input			break_input2			break_input3_heredoc	break_input4_heredoc						\
				break_input5_redi																									\
				ft_free				ft_other1				ft_other2				ft_other3									\
				ft_clean1				ft_clean2																					\
				execute_mini_unit_ft_execve\
				execute_mini_unit_redi\
				execute_mini_unit\
				execute_mini\
				execute_sub_mini
MINI_SRC		= $(patsubst %, ./mini/%.c, $(MINI))
MINI_OBJ		= $(patsubst %.c, %.o, $(MINI_SRC))
SRC				= $(PROMPT_SRC) $(BLTIN_SRC) $(ENV_SRC)
OBJS			= $(patsubst %.c, ./src/%.o, $(SRC)) $(MINI_OBJ)
LIBFT			= libft/libft.a
NAME			= minishell

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HDR_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LFLAGS) $(HDR_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) 

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