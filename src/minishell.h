/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/10 17:41:06 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <readline/readline.h> // Include readline header
# include <libft.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_save
{
	char			**env;
	char			**path_system;
}	t_save;

typedef struct s_exec
{
	char			*cmd;
	int				argc;
	char			**argv;
	char			**env;
	int				exit_code;
}	t_exec;

int				ft_create_n_modify_env(t_save *save, char *str_of_add_rule,
					int add_replace_remove);
int				ft_save_path_system_n_env_init(t_save *save,
					char **env_outside);
int				 exec_builtin(t_exec exec);
#endif
