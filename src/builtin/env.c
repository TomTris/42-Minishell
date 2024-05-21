/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:25:04 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/21 13:51:15 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	on_env(t_exec e)
{
	char	**env;
	int		i;

	(void)e;
	i = -1;
	set_env_variable("_", "/usr/bin/env");
	env = get_env()->env;
	while (env[++i])
		ft_printf("%s\n", env[i]);
}
