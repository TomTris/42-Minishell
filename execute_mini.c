/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:37:59 by qdo               #+#    #+#             */
/*   Updated: 2024/05/24 00:00:17 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_execute_mini2(t_mini *mini, int i, int status)
{
	int	code;

	if (status == -2)
		code = exit_code(-1);
	else if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		code = WTERMSIG(status) + 128;
	else
		return (print_err("sth i don't know yet\n"), exit_code(1), -1);
	exit_code(code);
	while (i <= mini->sub_mini[0].nbr)
	{
		if ((code == 0 && mini->sub_mini[i].sign_after == 2)
			|| (code != 0 && mini->sub_mini[i].sign_after == 1))
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
	int	status;
	int	fd_reserve;
	int	fd_reserve2;

	fd_reserve = ft_fd_dup(dup(STDIN_FILENO));
	if (fd_reserve == -1)
		return (exit_code(1), perror("ft_fd_dup"), 1);
	fd_reserve2 = ft_fd_dup(dup(STDOUT_FILENO));
	if (fd_reserve2 == -1)
		return (exit_code(1), perror("ft_fd_dup"), 1);
	i = 1;
	while (i <= mini->sub_mini[0].nbr)
	{
		status = ft_execute_sub_mini(&(mini->sub_mini[i]));
		if (dup2(fd_reserve, STDIN_FILENO) == -1
			|| dup2(fd_reserve2, STDOUT_FILENO) == -1)
			return (exit_code(1), perror("dup2"), 1);
		if (status == -1)
			return (exit_code(-1));
		i = ft_execute_mini2(mini, i, status);
	}
	return (exit_code(-1));
}
