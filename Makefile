CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
NAME = minishell
LIBFT_DIR = libft
LIBFT_A = libft/libft.a

OBJ_DIR = obj

SRC = \
		mini_mini.c\
		mini_sub_mini.c\
		mini_mini_unit.c\
		mini_mini_start.c\
		syntax_precheck.c\
		syntax_check.c\
		expansion_0.c\
		expansion_dollar1.c\
		expansion_dollar2.c\
		expansion_dollar3.c\
		expansion_dollar4.c\
		expansion_wildcard1.c\
		expansion_wildcard2.c\
		break_input.c\
		break_input2.c\
		break_input3_heredoc.c\
		break_input4_heredoc.c\
		break_input5_heredoc.c\
		break_input5_redi.c\
		ft_free.c\
		ft_other1.c\
		ft_other2.c\
		ft_other3.c\
		ft_clean1.c\
		ft_clean2.c\
		execute_mini_unit_ft_execve.c \
		execute_mini_unit_redi.c\
		execute_mini_unit_ft_execve_gen.c\
		execute_mini_unit_ft_execve2.c\
		execute_mini_unit.c\
		execute_mini.c\
		execute_sub_mini.c\
		execute_sub_mini_helper.c\
		ft_builtin_env.c\
		ft_builtin_cd.c\
		ft_builtin_cd_bonus.c\
		ft_builtin_unset.c\
		ft_builtin_export.c \
		ft_builtin_export2.c \
		ft_builtin_add_rm.c\
		ft_builtin_echo.c\
		ft_builtin_pwd.c\
		ft_builtin_exit.c\
		signal.c
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir obj

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
