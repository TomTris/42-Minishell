/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sub_mini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:56:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/18 03:55:54 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_sig_ter(pid_t *pid, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		kill(pid[i], SIGTERM);
}

//status here to check and get exit code

int	ft_wait_pid(pid_t *pid, int nbr)
{
	int	status;
	int	i;

	if (waitpid(pid[nbr - 1], &status, 0) == -1)
		return (perror("waitpid"), 1);
	i = 0;
	while (++i < nbr)
		if (wait(0) == -1)
			return (perror("wait"), 1);
	return (status);
}

pid_t	*pid_arr_create(int i)
{
	pid_t	*ret;

	ret = (pid_t *)malloc(i * sizeof(pid_t));
	if (ret == 0)
		return (perror("malloc failed"), NULL);
	return (ret);
}

int	ft_execute_sub_mini2(t_sub_mini *sub_mini)
{
	int		i;
	int		fd_in;
	int		status;
	pid_t	*pid;

	pid = pid_arr_create(sub_mini->mini_unit[0].nbr);
	if (pid == NULL)
		return (0);
	fd_in = -2;
	i = 0;
	while (++i <= sub_mini->mini_unit[0].nbr && fd_in != -1)
	{
		fd_in = ft_recursion_muni_unit_create(
				pid, &(sub_mini->mini_unit[i]), fd_in);
	}
	if (fd_in == -1)
		return (ft_sig_ter(pid, i - 1), free(pid), 0);
	status = ft_wait_pid(pid, i - 1);
	if (WIFEXITED(status))
		return (free(pid), WEXITSTATUS(status) + 1);
	ft_sig_ter(pid, i - 1);
	free(pid);
	return (0);
}


int	ft_execute_sub_mini(t_sub_mini *sub_mini)
{
	pid_t	pid;
	int		status;

	if (sub_mini->mini_unit[0].nbr == 1)
	{
		if (ft_redi_execute(&(sub_mini->mini_unit[1])) == 0)
			return (0);
		if (sub_mini->mini_unit[1].cmd == 0 && sub_mini->mini_unit[1].mini == 0)
			return (1);
		if (sub_mini->mini_unit[1].cmd == 0 && sub_mini->mini_unit[1].mini != 0)
			return (ft_execute_mini(sub_mini->mini_unit[1].mini));
		if (ft_is_builtin(&sub_mini->mini_unit[1]) == 1)
			return (ft_builtin(&(sub_mini->mini_unit[1].cmd)));
		pid = fork();
		if (pid == -1)
			return (perror("fork"), ft_clean_programm(0, EXIT_FAILURE));
		if (pid == 0)
			exit(ft_execute_mini_unit(&(sub_mini->mini_unit[1]), -1, -1));
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status) + 1);
		return (0);
	}
	else
		return (ft_execute_sub_mini2(sub_mini));
}
