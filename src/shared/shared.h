/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:09:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/21 13:52:58 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <minishell.h>

typedef struct s_env_var
{
	char		*name;
	char		*value;
}	t_env_var;

typedef struct s_shared
{
	char	**env;
	int		exit_code;
	char	*cwd;
	char	*oldcwd;
	char	*home;
	char	*last_arg;
}	t_shared;

int				ft_create_n_modify_env(t_shared *save, char *rule, int mode);
int				ft_env_init(t_shared *save, char **env_outside);
void			set_oldpwd(char *oldcwd);
void			set_cwd(char *cwd);
t_shared		*get_env(void );
int				set_env(char **env);
char			*get_env_variable(char *var_name);
int				set_env_variable(char *var_name, char	*var_value);
void			free_exit(int signum);
void			set_exit_code(int code);
t_env_var		*get_name_value(char *env_line);

// utils
void			print_prompt(void);
int				ft_arr_len(char **arr);
int				is_valid_int(char *arg);
void			ft_sort_ascii(char **ret);
#endif