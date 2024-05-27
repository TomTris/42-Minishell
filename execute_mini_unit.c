/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini_unit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:15:49 by qdo               #+#    #+#             */
/*   Updated: 2024/05/27 16:32:42 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_builtin(char **cmd, char ***env_o)
{
	if (sncmp(cmd[0], "export", 7) == 1)
		return (ft_export(env_o, cmd));
	if (sncmp(cmd[0], "unset", 6) == 1)
		return (ft_unset(env_o, cmd));
	if (sncmp(cmd[0], "echo", 5) == 1)
		return (ft_echo(cmd));
	if (sncmp(cmd[0], "pwd", 4) == 1)
		return (ft_pwd());
	if (sncmp(cmd[0], "env", 4) == 1)
		return (ft_builtin_env(*env_o));
	if (sncmp(cmd[0], "exit", 5) == 1)
		return (ft_exit(cmd));
	if (sncmp(cmd[0], "cd", 3) == 1)
		return (ft_cd(cmd, env_o));
	perror("sthwrong in ft_builtin\n");
	return (0);
}

int	ft_is_builtin(t_mini_unit *mini_unit)
{
	if (mini_unit->cmd == 0 || mini_unit->cmd[0] == 0)
		return (0);
	if (sncmp(mini_unit->cmd[0], "cd", 3) == 1
		|| sncmp(mini_unit->cmd[0], "echo", 5) == 1
		|| sncmp(mini_unit->cmd[0], "pwd", 4) == 1
		|| sncmp(mini_unit->cmd[0], "export", 7) == 1
		|| sncmp(mini_unit->cmd[0], "unset", 6) == 1
		|| sncmp(mini_unit->cmd[0], "env", 4) == 1
		|| sncmp(mini_unit->cmd[0], "exit", 5) == 1)
		return (1);
	return (0);
}

int	ft_execute_mini_unit(t_mini_unit *mini_unit, int fd_in, int fd_out)
{
	if (fd_in >= 0)
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (exit_code(1), perror("dup2"),
				ft_clean_programm(0, 1));
	if (fd_in >= 0)
		close(fd_in);
	if (mini_unit->nbr != mini_unit->nbr_sum)
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (exit_code(1), perror("dup2"),
				ft_clean_programm(0, 1));
	if (ft_redi_execute(mini_unit) == 0)
		return (ft_clean_programm(0, 1));
	if (mini_unit->cmd == 0 && mini_unit->mini != 0)
		return (exit_code(ft_execute_mini(mini_unit->mini)),
			ft_clean_programm(0, 1));
	else if (mini_unit->cmd == 0 && mini_unit->mini == 0)
		return (exit_code(0), ft_clean_programm(0, 1));
	else if (ft_is_builtin(mini_unit) == 1)
		return (ft_builtin(mini_unit->cmd, mini_unit->env_ori),
			ft_clean_programm(0, 1));
	else
		return (ft_execve(mini_unit, fd_out), -99);
	return (perror("sth ft_execute_mini_unit"), exit_code(99),
		ft_clean_programm(0, 1), -99);
}

int	ft_recursion_muni_unit_create(
		pid_t *pid_arr, t_mini_unit *mini_unit, int fd_in)
{
	int		fd_new[2];
	pid_t	pid;

	if (pipe(fd_new) == -1)
		return (exit_code(1), perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ft_sig_2);
		signal(SIGQUIT, ft_sig_2);
		close(fd_new[0]);
		ft_execute_mini_unit(mini_unit, fd_in, fd_new[1]);
	}
	pid_arr[mini_unit->nbr - 1] = pid;
	close(fd_new[1]);
	if (fd_in >= 0)
		close(fd_in);
	return (fd_new[0]);
}
