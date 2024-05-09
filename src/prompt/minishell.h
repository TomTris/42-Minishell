/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 14:12:16 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <readline/readline.h> // Include readline header
# include <libft.h>

typedef struct s_save
{
	char			**env;
	char			**path_system;
}	t_save;

int				ft_create_n_modify_env(t_save *save, char *str_of_add_rule,
					int add_replace_remove);
int				ft_save_path_system_n_env_init(t_save *save,
					char **env_outside);



#endif
