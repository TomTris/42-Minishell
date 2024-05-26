/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini_unit_ft_execve.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:55:45 by qdo               #+#    #+#             */
/*   Updated: 2024/05/26 23:01:46 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_execve_dot_stat(t_mini_unit *mini_unit, struct stat *path_stat)
{
	if (S_ISDIR((*path_stat).st_mode))
	{
		if (print_fd(2, "%s: Is a directory\n",
				mini_unit->cmd[0]) == -1)
			return (exit_code(1), perror("print_fd"),
				ft_clean_programm(0, 1), -9);
		return (exit_code(126), ft_clean_programm(0, 1), -9);
	}
	if (S_ISREG((*path_stat).st_mode))
	{
		execve(mini_unit->cmd[0],
			mini_unit->cmd, *(mini_unit->env_ori));
		return (exit_code(126), perror("mini_unit->cmd[0]"),
			ft_clean_programm(0, 1), -9);
	}
	return (1);
}

int	ft_execve3(t_mini_unit *mini_unit, struct stat *path_stat)
{
	if (mini_unit->cmd[0][0] == '.')
	{
		if (mini_unit->cmd[0][1] == 0)
			ft_execve_dot0();
		if (stat(mini_unit->cmd[0], path_stat) == 0)
			ft_execve_dot_stat(mini_unit, path_stat);
		exit_code(127);
		if (print_fd(2, "%s: No such file or directory\n",
				mini_unit->cmd[0]) == -1)
			return (exit_code(1), perror("print_fd"), -9);
		ft_clean_programm(0, 1);
	}
	return (1);
}

int	ft_execve_2_5(t_mini_unit *unit, struct stat *path_stat)
{
	if (S_ISDIR((*path_stat).st_mode))
	{
		if (print_fd(2, "%s: Is a directory\n", unit->cmd[0]) == -1)
			return (exit_code(1), perror("print_fd"),
				ft_clean_programm(0, 1), -9);
		return (exit_code(126), ft_clean_programm(0, 1), -9);
	}
	else if (S_ISREG((*path_stat).st_mode))
	{
		if (execve(unit->cmd[0], unit->cmd, *(unit->env_ori)) == -1)
			return (perror(unit->cmd[0]), exit_code(2),
				ft_clean_programm(0, 1), -9);
	}
	exit_code(127);
	if (print_fd(2, "%s: No such file or directory\n", unit->cmd[0]) == -1)
		return (exit_code(1), perror("print_fd"), -9);
	ft_clean_programm(0, 1);
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
		{
			exit_code(127);
			if (print_fd(2,
					"%s: No such file or directory\n", unit->cmd[0]) == -1)
				return (exit_code(1), perror("print_fd"), -9);
			ft_clean_programm(0, 1);
		}
	}
	return (ft_execve3(unit, &path_stat));
}

int	ft_execve(t_mini_unit *mini_unit, int fd_close)
{
	char	**path;

	if (mini_unit->cmd[0][0] == '\0')
	{
		exit_code(127);
		if (fd_close >= 0)
			close(fd_close);
		if (print_fd(2, ": command not found\n") == -1)
			return (exit_code(1), perror("print_fd"),
				ft_clean_programm(0, 1), -9);
		ft_clean_programm(0, 1);
	}
	if (mini_unit->cmd[0][0] != '.' || mini_unit->cmd[0][1] != '.' || mini_unit->cmd[0][2] != '\0')
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
