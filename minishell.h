/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 10:56:21 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <readline/readline.h> // Include readline header
# include "libft/libft.h"

typedef struct s_groups_break
{
	char	or_sign[3];
	char	and_sign[3];
	char	doublequote[2];
	char	singlequote[2];
	char	parenthesis_open[2];
	char	parenthesis_close[2];
	char	pipe_sign[2];
}	t_groups_break;

# define DOUBLEQUOTE 1
# define SINGLEQUOTE 2
# define OR_SIGN 3
# define AND_SIGN 4
# define PIPE_SIGN 5
# define PARENTHESIS_OPEN 6
# define PATHENTHESIS_CLOSE 7

// nothing		0;
// doublequote	1
// singlequote	2
// or_sign		3
// and_sign		4
// pipe_sign	5;
// parenthesis_open		6;
// parenthesis_close	7;
typedef struct s_input_break
{
	int		nbr;
	int		in_fd;
	int		out_fd;
	int		sign_before;
	int		sign_after;
	char	*str;
}	t_input_break;

typedef struct s_save
{
	char			**env;
	char			**path_system;
	t_groups_break	groups_break;
	t_input_break	*input_break;
}	t_save;

int				ft_create_n_modify_env(t_save *save, char *str_of_add_rule,
					int add_replace_remove);
int				ft_save_path_system_n_env_init(t_save *save,
					char **env_outside);


t_input_break	*ft_input_break_create(char *str);
int				ft_cnt_inputs(char *str);


int				ft_input_check_parenthesis_n_quotes(char *str);
int				ft_check_parenthesis_closed(char *str);
int				ft_check_quotes(char *str, int i, char *temp);
int				ft_is_only_empty(char *str_start, char *str_end);

#endif
