/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 14:07:02 by bpisak-l         ###   ########.fr       */
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
# include <string.h> //for strerror

typedef struct s_save
{
	char			**env;
	char			**path_system;
}	t_save;

typedef struct s_shared
{
	t_save	*env_vars;
}	t_shared;

typedef struct s_exec
{
	char			*cmd;
	int				argc;
	char			**argv;
	char			**env;
	int				exit_code;
}	t_exec;

//env
t_shared		*get_env(void );
int				set_env(char **env);
char			*get_env_variable(char *var_name);

// builtins
int				exec_builtin(t_exec exec);

// utils
int				ft_arr_len(char **arr);
int				is_valid_int(char *arg);
#endif
