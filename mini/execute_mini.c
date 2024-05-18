/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:37:59 by qdo               #+#    #+#             */
/*   Updated: 2024/05/18 03:37:54 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_execute_mini2(t_mini *mini, int i, int j)
{
	while (i <= mini->sub_mini[0].nbr)
	{
		if (j != mini->sub_mini[i].sign_after)
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
	int	fd_reserve2;

	fd_reserve = dup(STDIN_FILENO);
	if (fd_reserve == -1)
		return (perror("ft_fd_dup"), 0);
	fd_reserve2 = dup(STDOUT_FILENO);
	if (fd_reserve2 == -1)
		return (close(fd_reserve2), perror("ft_fd_dup"), 0);
	i = 1;
	while (i <= mini->sub_mini[0].nbr)
	{
		j = ft_execute_sub_mini(&(mini->sub_mini[i]));
		if (j == 0)
			return (close(fd_reserve), close(fd_reserve2), 0);
		if (dup2(fd_reserve, STDIN_FILENO) == -1
			|| dup2(fd_reserve2, STDOUT_FILENO) == -1)
			return (close(fd_reserve), close(fd_reserve2), perror("dup2"), 0);
		i = ft_execute_mini2(mini, i, j);
	}
	close(fd_reserve);
	close(fd_reserve2);
	return (1);
}
