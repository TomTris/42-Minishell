/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sub_mini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:56:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/23 23:46:05 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//status here to check and get exit code
int	ft_wait_pid(pid_t *pid, int nbr)
{
	int	status;
	int	i;

	if (waitpid(pid[nbr - 1], &status, 0) == -1)
		return (exit_code(1), ft_sig_ter(pid, nbr), perror("waitpid"), -1);
	i = 0;
	while (++i < nbr)
		if (wait(0) == -1)
			return (ft_sig_ter(pid, nbr), exit_code(1), perror("wait"), -1);
	return (status);
}

int	ft_execute_sub_mini2(t_sub_mini *sub_mini)
{
	int		i;
	int		fd_in;
	int		status;
	pid_t	*pid;

	pid = (pid_t *)malloc(sub_mini->mini_unit[0].nbr * sizeof(pid_t));
	if (pid == 0)
		return (exit_code(1), perror("malloc failed"), 0);
	fd_in = -2;
	i = 0;
	while (++i <= sub_mini->mini_unit[0].nbr && fd_in != -1)
	{
		fd_in = ft_recursion_muni_unit_create(
				pid, &(sub_mini->mini_unit[i]), fd_in);
	}
	if (fd_in == -1)
		return (ft_sig_ter(pid, i - 1), free(pid), -1);
	close(fd_in);
	status = ft_wait_pid(pid, i - 1);
	free(pid);
	return (status);
}

//-1 - sth wrong.
//-2. Use exit_code(-1) to get exit_code
int	ft_execute_sub_mini_1(t_sub_mini *sub_mini)
{
	if (dollar_underscore(sub_mini->mini_unit[1].cmd, 0, 0) == 0)
		return (-1);
	if (env_underscore(sub_mini->mini_unit[1].cmd, sub_mini->env_ori) == 0)
		return (-1);
	if (ft_redi_execute(&(sub_mini->mini_unit[1])) == 0)
		return (-1);
	if (sub_mini->mini_unit[1].cmd == 0 && sub_mini->mini_unit[1].mini == 0)
		return (exit_code(0), -2);
	if (ft_is_builtin(&sub_mini->mini_unit[1]) == 1)
	{
		if (ft_builtin(sub_mini->mini_unit[1].cmd,
				sub_mini->mini_unit[0].env_ori) == 0)
			return (-1);
		return (-2);
	}
	return (1);
}

void	ft_child_1(t_sub_mini *sub_mini)
{
	signal(SIGINT, ft_sig_2);
	signal(SIGQUIT, ft_sig_2);
	if (sub_mini->mini_unit[1].cmd == 0
		&& sub_mini->mini_unit[1].mini != 0)
	{
		exit_code(ft_execute_mini(sub_mini->mini_unit[1].mini));
		ft_clean_programm(0, 1);
	}
	exit(ft_execute_mini_unit(&(sub_mini->mini_unit[1]), -1, -1));
}

//return -1 - sth wrong.
//return -2 => exit_code already set, code = exit_code(-1);
int	ft_execute_sub_mini(t_sub_mini *sub_mini)
{
	pid_t	pid;
	int		i;
	int		status;

	if (sub_mini->mini_unit[0].nbr == 1)
	{
		i = ft_execute_sub_mini_1(sub_mini);
		if (i == -1 || i == -2)
			return (i);
		pid = fork();
		if (pid == -1)
			return (exit_code(1), perror("fork"),
				ft_clean_programm(0, EXIT_FAILURE));
		if (pid == 0)
			ft_child_1(sub_mini);
		status = ft_wait_pid(&pid, 1);
		return (status);
	}
	return (ft_execute_sub_mini2(sub_mini));
}
