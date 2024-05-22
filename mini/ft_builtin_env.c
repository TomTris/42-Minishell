/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 07:55:54 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:47:10 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (printf("%s\n", env[i++]) == -1)
			return (exit_code(1), perror("printf"), exit_code(2), 0);
	}
	exit_code(0);
	return (1);
}
