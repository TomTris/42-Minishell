/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/08 06:51:42 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <readline/readline.h> // Include readline header
# include "libft/libft.h"

typedef struct s_groups_break
{
	char	doublequote[2];
	char	singlequote[2];
	char	or_sign[3];
	char	and_sign[3];
	char	parenthesis_open[2];
	char	parenthesis_close[2];
	char	pipe_sign[2];
}	t_groups_break;

// nothing		0;
// doublequote	1
// singlequote	2
// or_sign		3
// and_sign		4
// parenthesis_open		5;
// parenthesis_close	6;
// pipe_sign	7;

typedef struct s_save
{
	int				in_fd;
	int				out_fd;
	char			**env;
	char			**path_system;
	t_groups_break	groups_break;
	t_input_break	*input_break;
}	t_save;

typedef struct s_input_break
{
	int		sign_before;
	int		sign_after;
	char	*str;
}	t_input_break;

int	ft_create_n_modify_env(t_save *save, char *str_of_add_rule,
		int add_replace_remove);
int	ft_save_path_system_n_env_init(t_save *save, char **env_outside);

#endif
