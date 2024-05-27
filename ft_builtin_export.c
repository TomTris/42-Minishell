/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:06:26 by qdo               #+#    #+#             */
/*   Updated: 2024/05/27 17:35:03 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	export_0_args(char **env, int i)
{
	int	j;

	i = 0;
	while (env[i])
	{
		if ((env[i][0] != '_' || env[i][1] != '='))
		{
			if (printf("%s", "declare -x ") == -1)
				return (perror("printf"), 0);
			j = 0;
			while (env[i][j] != '=')
				if (printf("%c", env[i][j++]) == -1)
					return (perror("printf"), 0);
			if (printf("=%c", '"') == -1)
				return (perror("printf"), 0);
			j++;
			while (env[i][j] != 0)
				if (printf("%c", env[i][j++]) == -1)
					return (perror("printf"), 0);
			if (printf("%c\n", '"') == -1)
				return (perror("printf"), 0);
		}
		i++;
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
			if (print_fd(2, "export: `%s': not a valid identifier\n", cmd[i])
				== -1)
				return (perror("print_fd"), 0);
			*check = 1;
			*check2 = 1;
		}
	}
	return (1);
}

int	ft_export2(char ***env_o, char **cmd, int *check2)
{
	int	i;
	int	check;

	i = 0;
	while (cmd[++i])
	{
		if (ft_is_exportpp(cmd, i) == 1)
		{
			if (ft_exportpp(env_o, cmd, i) == 0)
				return (exit_code(1), 0);
		}
		else
		{
			check = 0;
			if (ft_check_identifier(cmd, i, &check, check2) == 0)
				return (exit_code(1), 0);
			if (check == 0)
				if (ft_strchr(cmd[i], '=') != NULL)
					if (ft_env(env_o, cmd[i], 1) == 0)
						return (exit_code(1), 0);
		}
	}
	return (1);
}

int	ft_export(char ***env_o, char **cmd)
{
	int		check2;

	check2 = 0;
	if (cmd != 0 && cmd[0] != 0 && cmd[1] == 0)
		return (export_0_args(*env_o, 0));
	ft_export2(env_o, cmd, &check2);
	exit_code(1);
	if (check2 == 0)
		exit_code(0);
	return (1);
}
