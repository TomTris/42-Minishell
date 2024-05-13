/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:09:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 13:46:28 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <minishell.h>

int				ft_create_n_modify_env(t_save *save, char *str_of_add_rule,
					int add_replace_remove);
int				ft_save_path_system_n_env_init(t_save *save,
					char **env_outside);

#endif