/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:06:26 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 03:23:59 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	export_0_args(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		printf("%s", "declare -x ");
		j = 0;
		while (env[i][j] != '=')
			printf("%c", env[i][j++]);
		printf("%c", '"');
		j++;
		while (env[i][j] != 0)
			printf("%c", env[i][j++]);
		printf("%c\n", '"');
	}
	return (1);
}

int	ft_check_identifier(char **cmd, int i, int *check, int *check2)
{
	int	j;

	if (ft_isdigit(cmd[i][0]) == 1 || ft_isalnum_(cmd[i][0]) != 1)
	{
		if (print_fd(2, "export: `%s': not a valid identifier\n", cmd[i]) == -1)
			return (perror("print_fd"), 0);
		*check = 1;
		*check2 = 1;
	}
	j = -1;
	while (cmd[i][++j] && cmd[i][j] != '=')
	{
		if (ft_isalnum_(cmd[i][j]) != 1)
		{
			if (print_fd(2, "export: `%s': not a valid identifier\n", cmd[i]) == -1)
				return (perror("print_fd"), 0);
			*check = 1;
			*check2 = 1;
		}
	}
	return (1);
}

//ft_export(env, 0) => declare bla bla
int	ft_export(char ***env_o, char **cmd)
{
	int		i;
	int		check;
	int		check2;

	if (cmd == 0)
		return (export_0_args(*env_o));
	check2 = 0;
	i = 0;
	while (cmd[++i])
	{
		check = 0;
		if (ft_check_identifier(cmd, i, &check, &check2) == 0)
			return (exit_code(1), 0);
		if (check == 0)
			if (ft_strchr(cmd[i], '=') != NULL)
				if (ft_env(env_o, cmd[i], 1) == 0)
					return (exit_code(1), 0);
	}
	exit_code(1);
	if (check2 == 0)
		exit_code(0);
	return (1);
}
