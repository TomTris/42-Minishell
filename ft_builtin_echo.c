/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 06:22:24 by qdo               #+#    #+#             */
/*   Updated: 2024/05/26 22:02:33 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_after_option(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			j = 1;
			while (cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] != 0)
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	ft_print_rest(char **cmd, int i, int option)
{
	int	j;

	j = i;
	if (cmd[i] != 0)
	{
		if (printf("%s", cmd[i]) == -1)
			return (exit_code(1), perror("printf"), 0);
		while (cmd[++i])
			if (printf(" %s", cmd[i]) == -1)
				return (exit_code(1), perror("printf"), 0);
		if (option == 0)
			if (printf("\n") == -1)
				return (exit_code(1), perror("printf"), 0);
		exit_code(0);
		return (1);
	}
	if (j == i && i == 1)
		if (printf("\n") == -1)
			return (exit_code(1), perror("printf"), 0);
	exit_code(0);
	return (1);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	option;

	i = ft_after_option(cmd);
	option = 0;
	if (i > 1)
		option = 1;
	return (ft_print_rest(cmd, i, option));
}
