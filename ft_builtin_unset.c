/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:34:59 by qdo               #+#    #+#             */
/*   Updated: 2024/05/23 09:28:16 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_identifier_unset2(char **cmd, int i)
{
	int	j;

	if (ft_isdigit(cmd[i][0]) == 1 || ft_isalnum_(cmd[i][0]) != 1)
	{
		return (0);
	}
	j = -1;
	while (cmd[i][++j])
	{
		if (ft_isalnum_(cmd[i][j]) != 1)
		{
			return (0);
		}
	}
	return (1);
}

int	ft_unset(char ***env_o, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (ft_check_identifier_unset2(cmd, i) == 0)
			exit_code(0);
		else
			if (ft_env(env_o, cmd[i], -1) == 0)
				return (exit_code(1), 0);
	}
	return (1);
}
