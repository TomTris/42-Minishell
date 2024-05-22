/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:34:59 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 09:22:38 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_check_identifier_unset2(char **cmd, int i, int *check, int *check2)
{
	int	j;

	if (ft_isdigit(cmd[i][0]) == 1 || ft_isalnum_(cmd[i][0]) != 1)
	{
		if (print_fd(2, "unset: `%s': not a valid identifier\n", cmd[i]) == -1)
			return (perror("print_fd"), 0);
		*check = 1;
		*check2 = 1;
	}
	j = -1;
	while (cmd[i][++j])
	{
		if (ft_isalnum_(cmd[i][j]) != 1)
		{
			if (print_fd(2, "unset: `%s': not a valid identifier\n",
					cmd[i]) == -1)
				return (perror("print_fd"), 0);
			*check = 1;
			*check2 = 1;
		}
	}
	return (1);
}

int	ft_unset(char ***env_o, char **cmd)
{
	int	i;
	int	check;
	int	check2;

	i = 0;
	check2 = 0;
	while (cmd[++i])
	{
		check = 0;
		if (ft_check_identifier_unset2(cmd, i, &check, &check2) == 0)
			return (exit_code(1), 0);
		if (check == 0)
			if (ft_env(env_o, cmd[i], -1) == 0)
				return (exit_code(1), 0);
	}
	exit_code(1);
	if (check2 == 0)
		exit_code(2);
	return (1);
}
