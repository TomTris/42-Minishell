/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:09:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/15 17:30:25 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <minishell.h>

typedef struct s_save
{
	char			**env;
	char			**path_system;
}	t_save;

typedef struct s_shared
{
	t_save	*env_vars;
	int		*exit_code;
	char	*cwd;
	char	*oldcwd;
}	t_shared;

int				ft_create_n_modify_env(t_save *save, char *rule, int mode);
int				ft_save_path_system_n_env_init(t_save *save, char **env_outside);
void			set_oldpwd(char *oldcwd);
void			set_cwd(char *cwd);
t_shared		*get_env(void );
int				set_env(char **env);
char			*get_env_variable(const char *var_name);
int				set_env_variable(char *var_name, char	*var_value);
void			free_exit(int signum);
void			set_exit_code(int code);

#endif