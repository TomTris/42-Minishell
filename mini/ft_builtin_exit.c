/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 07:03:45 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 07:52:08 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_exit_first_args_non_numeric(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1][i] == '-' || cmd[1][i] == '+')
		i++;
	while (cmd[1][i])
	{
		if (ft_isdigit(cmd[1][i++]) != 1)
			return (1);
	}
	return (0);
}

int	ft_exit_num_too_big(char *cmd, int i, int sign)
{
	i = 0;
	sign = 0;
	if (cmd[0] == '+' || cmd[0] == '-')
	{
		sign = 1;
		i = 1;
	}
	while (cmd[i])
		i++;
	if (i - sign > 19)
		return (1);
	if (i - sign < 19)
		return (0);
	i = sign;
	if (cmd[i] < '9' || cmd[i + 1] < '2')
		return (1);
	if (cmd[i + 1] > '2' || cmd[i + 2] > '2' || cmd[i + 3] > '3'
		|| cmd[i + 4] > '3' || cmd[i + 5] > '7' || cmd[i + 6] > '2'
		|| cmd[i + 7] > '0' || cmd[i + 8] > '3' || cmd[i + 9] > '6'
		|| cmd[i + 10] > '8' || cmd[i + 11] > '5' || cmd[i + 12] > '4'
		|| cmd[i + 13] > '7' || cmd[i + 14] > '7' || cmd[i + 15] > '5'
		|| cmd[i + 16] > '8' || cmd[i + 17] > '0'
		|| (cmd[0] != '-' && cmd[i + 18] > '8'))
		return (1);
	return (0);
}

int	ft_exit(char **cmd)
{
	if (cmd[1] == NULL)
		ft_clean_programm(0, 1);
	if (ft_exit_first_args_non_numeric(cmd) == 1
		|| ft_exit_num_too_big(cmd[1], 0, 0) == 1)
	{
		exit_code(255);
		if (printf("%s: numberic argument required\n", cmd[1]) == -1)
		{
			exit_code(1);
			perror("printf");
			return (0);
		}
		ft_clean_programm(0, 1);
	}
	if (cmd[2] != 0)
	{
		exit_code(1);
		if (printf("exit: too many arguments\n") == -1)
			perror("printf");
		return (0);
	}
	exit_code(((ft_atoi(cmd[1]) % 255) + 255) % 255);
	ft_clean_programm(0, 1);
	return (-9);
}
