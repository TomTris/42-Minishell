/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini_unit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:15:49 by qdo               #+#    #+#             */
/*   Updated: 2024/05/18 16:58:09 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_builtin(char ***cmd)
{
	printf("get inside builtin\n");
	if (cmd == 0)
		return (perror("ft_builtin"), 0);
	return (1);
}

int	ft_is_builtin(t_mini_unit *mini_unit)
{
	if (mini_unit->cmd == 0 || mini_unit->cmd[0] == 0)
		return (0);

	if (sncmp(mini_unit->cmd[0], "cd", 3) == 1)
		// || sncmp(mini_unit->cmd[0], "echo", 5) == 1
		// || sncmp(mini_unit->cmd[0], "pwd", 4) == 1
		// || sncmp(mini_unit->cmd[0], "export", 7) == 1
		// || sncmp(mini_unit->cmd[0], "unset", 6) == 1)
		// || sncmp(mini_unit->cmd[0], "env", 4) == 1
		// || sncmp(mini_unit->cmd[0], "exit", 5) == 1)
		return (1);
	return (0);
}

int	ft_execute_mini_unit(t_mini_unit *mini_unit, int fd_in, int fd_out)
{
	if (fd_in >= 0)
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (perror("dup2"), ft_clean_programm(0, EXIT_FAILURE));
	close(fd_in);
	if (mini_unit->nbr != mini_unit->nbr_sum)
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (perror("dup2"), ft_clean_programm(0, EXIT_FAILURE));
	if (ft_redi_execute(mini_unit) == 0)
		return (0);
	if (mini_unit->cmd == 0 && mini_unit->mini != 0)
		return (ft_execute_mini(mini_unit->mini));
	else if (mini_unit->cmd == 0 && mini_unit->mini == 0)
		return (1);
	else if (ft_is_builtin(mini_unit) == 1)
		return (ft_builtin(&(mini_unit->cmd)));
	else
		return (ft_execve(mini_unit, fd_out), -99);
	return (perror("sth ft_execute_mini_unit"), -99);
}

int	ft_recursion_muni_unit_create(
		pid_t *pid_arr, t_mini_unit *mini_unit, int fd_in)
{
	int		fd_new[2];
	pid_t	pid;

	if (pipe(fd_new) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		close(fd_new[0]);
		exit(ft_execute_mini_unit(mini_unit, fd_in, fd_new[1]));
	}
	pid_arr[mini_unit->nbr - 1] = pid;
	close(fd_new[1]);
	close(fd_in);
	return (fd_new[0]);
}
