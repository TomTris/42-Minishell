/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini_unit_ft_execve.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:55:45 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:37:16 by qdo              ###   ########.fr       */
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
				return (exit_code(126), perror("execve"), free(temp2), 1);
		}
		free(temp2);
	}
	return (print_fd(2, "%s: Command not found\n", cmd));
}

int	ft_execve3(t_mini_unit *mini_unit)
{
	if (mini_unit->cmd[0][0] == '.')
	{
		if (mini_unit->cmd[0][1] == 0)
		{
			if (print_fd(2, ".: filename argument required\n") == -1
				|| print_fd(2, ".: usage: . filename [arguments]\n") == -1)
				return (exit_code(1), ft_clean_programm(0, 1), -9);
			exit_code(2);
			ft_clean_programm(0, 1);
		}
		if (execve(mini_unit->cmd[0],
				mini_unit->cmd, *(mini_unit->env_ori)) == -1)
			return (print_fd(2, "%s: Command not found\n", mini_unit->cmd[0]),
				exit_code(127), ft_clean_programm(0, 1), -9);
	}
	return (1);
}

int	ft_execve_2_5(t_mini_unit *unit, struct stat *path_stat)
{
	if (S_ISDIR((*path_stat).st_mode))
	{
		if (print_fd(2, "%s: is a directory\n", unit->cmd[0]) == -1)
			return (exit_code(1), perror("print_fd"),
				ft_clean_programm(0, 1), -9);
		return (exit_code(126), ft_clean_programm(0, 1), -9);
	}
	else if (S_ISREG((*path_stat).st_mode))
	{
		if (execve(unit->cmd[0], unit->cmd, *(unit->env_ori)) == -1)
			return (perror("execve"), exit_code(2),
				ft_clean_programm(0, 1), -9);
	}
	return (1);
}

int	ft_execve2(t_mini_unit *unit)
{
	struct stat	path_stat;

	if (unit->cmd[0][0] == '/')
	{
		if (stat(unit->cmd[0], &path_stat) == 0)
			ft_execve_2_5(unit, &path_stat);
		else
			return (exit_code(2), perror("stat"),
				ft_clean_programm(0, 1), -9);
		exit_code(127);
		if (print_fd(2, "%s: No such file or directory\n",unit->cmd[0]) == -1)
			return (exit_code(1), perror("print_fd"), -9);
		ft_clean_programm(0, 1);
		return (ft_execve3(unit));
	}
	return (ft_execve3(unit));
}

int	ft_execve(t_mini_unit *mini_unit, int fd_close)
{
	char	**path;

	if (mini_unit->cmd[0][0] == '\0')
	{
		exit_code(127);
		if (fd_close >= 0)
			close(fd_close);
		if (print_fd(2, ": Command not found\n") == -1)
			return (exit_code(1), perror("print_fd"),
				ft_clean_programm(0, 1), -9);
		ft_clean_programm(0, 1);
	}
	ft_execve2(mini_unit);
	path = ft_path_gen(*(mini_unit->env_ori));
	if (path == 0)
		ft_clean_programm(0, 1);
	ft_execve_absolut(
		mini_unit->cmd[0], mini_unit->cmd, path, *(mini_unit->env_ori));
	free_split(path);
	if (fd_close >= 0)
		close(fd_close);
	exit_code(127);
	ft_clean_programm(0, 1);
	return (-9);
}
