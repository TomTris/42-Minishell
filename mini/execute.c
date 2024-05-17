/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:15:49 by qdo               #+#    #+#             */
/*   Updated: 2024/05/17 15:57:03 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <minishell.h>


void	ft_sig_ter(pid_t *pid, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		kill(pid[i], SIGTERM);
}

pid_t	*pid_arr_create(int i)
{
	pid_t	*ret;

	ret = (pid_t *)malloc(i * sizeof(pid_t));
	if (ret == 0)
		return (perror("malloc failed"), NULL);
	return (ret);
}

int	ft_wait_pid(pid_t *pid, int nbr)
{
	int	status;
	int	i;

	if (waitpid(pid[nbr - 1], &status, 0) == -1)
		return (perror("waitpid"), 0);
	i = 0;
	while (++i < nbr)
		if (wait(0) == -1)
			return (perror("wait"), 0);
	return (1);
}

int	ft_redi_execute(t_mini_unit *mini_unit)
{
	int	i;
	int	fd_redi;

	i = -1;
	while (mini_unit->fd_heredoc[++i])
		dup2(mini_unit->fd_heredoc[i], STDIN_FILENO);
	i = 0;
	while (++i <= mini_unit->redi[0].type_re)
	{
		if (mini_unit->redi[i].type_re == APPEND)
			fd_redi = open(mini_unit->redi[i].str,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (mini_unit->redi[i].type_re == RE_OUT)
			fd_redi = open(mini_unit->redi[i].str,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			fd_redi = open(mini_unit->redi[i].str,
					O_RDONLY, 0644);
		if (fd_redi == -1)
			return (perror("open"), 0);
		ft_fd_redi_dup(fd_redi);
	}
	return (1);
}

int	ft_execv(t_mini_unit *mini_unit, int fd_close)
{
	// int		i;
	// char	**path;
	t_exec	*cmd_args;

	cmd_args = simple_parse(mini_unit->str);
	exec_builtin(*cmd_args);
	// ft_execv_relativ(mini_unit);
	// path = ft_path_gen(mini_unit);
	// ft_execv_absolut(mini_unit, path);
	close(fd_close);
	ft_clean_programm(0, EXIT_FAILURE, 0);
	return (1); //TODO:
}

int	ft_execute_mini_unit(t_mini_unit	*mini_unit, int fd_in, int fd_out)
{
	if (fd_in >= 0)
		dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	ft_redi_execute(mini_unit);
	if (mini_unit->cmd == 0 && mini_unit->mini != 0)
		return (ft_execute_mini(mini_unit->mini), - 99);
	else if (mini_unit->cmd == 0 && mini_unit->mini != 0)
		ft_clean_programm(0, EXIT_SUCCESS, 0);
	else
		ft_execv(mini_unit, fd_out);
	return (-99);
}

int	ft_recursion_fork_pid(pid_t *pid_arr, t_mini_unit *mini_unit, int fd_in)
{
	int		fd_new[2];
	pid_t	pid;

	if (pipe(fd_new) == 0)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == 0)
	{
		close(fd_new[0]);
		ft_execute_mini_unit(mini_unit, fd_in, fd_new[1]);
	}
	pid_arr[mini_unit->nbr - 1] = pid;
	close(fd_new[1]);
	return (fd_new[0]);
}

int	ft_execute_sub_mini(t_sub_mini *sub_mini)
{
	int		i;
	int		fd_in;
	pid_t	*pid;

	pid = pid_arr_create(sub_mini->mini_unit[0].nbr);
	if (pid == NULL)
		return (0);
	fd_in = -2;
	i = 0;
	while (++i <= sub_mini->mini_unit[0].nbr && fd_in != -1)
	{
		fd_in = ft_recursion_fork_pid(
				pid, &(sub_mini->mini_unit[i]), fd_in);
	}
	if (fd_in == -1)
		return (ft_sig_ter(pid, i - 1), free(pid), 0);
	if (ft_wait_pid(pid, i - 1) == 0)
		return (ft_sig_ter(pid, i - 1), free(pid), 0);
	return (1);
}

int	ft_execute_mini2(t_mini *mini, int i, int j)
{
	while (mini->sub_mini[i].sign_after != 0)
	{
		if (j == mini->sub_mini[i].sign_after)
		{
			i++;
			break ;
		}
		else
			i++;
	}
	return (i);
}

int	ft_execute_mini(t_mini *mini)
{
	int	i;
	int	j;
	int	fd_reserve;

	fd_reserve = ft_fd_dup(dup(STDIN_FILENO));
	if (fd_reserve == -1)
		return (perror("ft_fd_dup"), 0);
	i = 1;
	while (i <= mini->sub_mini[0].nbr)
	{
		if (dup2(fd_reserve, STDIN_FILENO) == -1)
			return (perror("dup2"), 0);
		j = ft_execute_sub_mini(&(mini->sub_mini[i]));
		if (j == 0)
			return (0);
		i = ft_execute_mini2(mini, i, j);
	}
	return (1);
}
