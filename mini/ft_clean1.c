/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:51:49 by qdo               #+#    #+#             */
/*   Updated: 2024/05/17 02:07:07 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	*ft_fd_heredoc_default(int fd_new)
{
	int	*fd;

	fd = (int *)malloc(2 * sizeof(int));
	if (fd == NULL)
	{
		print_err("malloc failed fd_create_fd_heredoc");
		return (NULL);
	}
	fd[0] = 1;
	fd[1] = fd_new;
	return (fd);
}

static int	*ft_fd_add(int *fd, int fd_new)
{
	int	i;
	int	*fd_arr_new;

	fd_arr_new = (int *)malloc((fd[0] + 2) * sizeof(int));
	if (fd_arr_new == NULL)
		return (NULL);
	fd_arr_new[0] = fd[0] + 1;
	i = 0;
	while (++i <= fd[0])
		fd_arr_new[i] = fd[i];
	fd_arr_new[i] = fd_new;
	return (fd_arr_new);
}

//fd_new = -1 -> close all of other fds
//return (-1) -> malloc failed.
//-> call this func again with ft_fd_heredoc(-1);
// else return >= 0
int	ft_fd_heredoc(int fd_new)
{
	static int	*fd = 0;
	int			*fd_temp;
	int			i;

	if (fd == 0 && fd_new >= 0)
	{
		fd = ft_fd_heredoc_default(fd_new);
		if (fd == 0)
			return (-1);
		return (fd_new);
	}
	if (fd_new < 0)
	{
		i = 0;
		if (fd != 0)
			while (++i <= fd[0])
				close(fd[i]);
		return (free(fd), fd = 0, -1);
	}
	fd_temp = ft_fd_add(fd, fd_new);
	if (fd_temp == NULL)
		return (-1);
	return (free(fd), fd = fd_temp, fd_new);
}

//heredoc delete - only ctrl D // exit.
int	ft_clean_programm(t_mini *mini_outside, int exit_nbr, int leaks_check)
{
	static t_mini	*mini = NULL;

	if (mini_outside != 0)
	{
		mini = mini_outside;
		return (1);
	}
	else
	{
		if (mini->env != 0)
			free_split(*(mini->env));
		free_mini(mini);
		free(mini);
		ft_fd_heredoc(-1);
		ft_fd_dup(-1);
		ft_fd_redi_dup(-1);
		unlink(HERE_DOC_FILE);
		if (leaks_check != 0)
			system("leaks mini");
		exit(exit_nbr);
		return (1);
	}
}