/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini_unit_ft_execve2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:05:36 by qdo               #+#    #+#             */
/*   Updated: 2024/05/23 21:26:02 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_execve_absolut(char *cmd, char **args, char **path, char **env)
{
	int		i;
	char	*temp;
	char	*temp2;

	if (path[0] == 0)
		return (print_fd(2, "%s: No such file or directory\n", cmd));
	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		if (temp == 0)
			return (exit_code(1), 0);
		temp2 = ft_strjoin(temp, cmd);
		free(temp);
		if (temp2 == 0)
			return (exit_code(1), 0);
		if (access(temp2, F_OK) == 0)
		{
			if (execve(temp2, args, env) == -1)
				return (exit_code(126), perror(temp2), free(temp2), 1);
		}
		free(temp2);
	}
	return (print_fd(2, "%s: command not found\n", cmd));
}

int	ft_execve_dot0(void)
{
	if (print_fd(2, ".: filename argument required\n") == -1
		|| print_fd(2, ".: usage: . filename [arguments]\n") == -1)
		return (perror("print_fd"), exit_code(1),
			ft_clean_programm(0, 1), -9);
	exit_code(2);
	ft_clean_programm(0, 1);
	return (-9);
}
