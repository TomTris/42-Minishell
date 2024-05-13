/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:27:06 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 14:10:44 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_shared	*get_env(void )
{
	static t_shared	vars;

	return (&vars);
}

int	set_env(char **env)
{
	t_shared	*vars;

	vars = get_env();
	vars->env_vars = ft_calloc(1, sizeof(t_save));
	return (ft_save_path_system_n_env_init(vars->env_vars, env));
}

char	*get_env_variable(char *var_name)
{
	printf("%s\n", var_name);
	return (var_name);
}
