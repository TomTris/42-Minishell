/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/08 05:32:36 by qdo              ###   ########.fr       */
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
	char	**new_input;
}	t_groups_break;

typedef struct s_save
{
	char	**env;
	char	**path_system;
}	t_save;

typedef struct s_begin_end
{
	int	i_begin;
	int	i_end;
}	t_begin_end;

int	ft_create_n_modify_env(t_save *save, char *str_of_add_rule,
		int add_replace_remove);
int	ft_save_path_system_n_env_init(t_save *save, char **env_outside);

#endif
