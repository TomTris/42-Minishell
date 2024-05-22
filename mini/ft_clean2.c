/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:50:03 by qdo               #+#    #+#             */
/*   Updated: 2024/05/21 18:32:07 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	*ft_fd_dup_default(int fd_new)
{
	int	*fd;

	fd = (int *)malloc(2 * sizeof(int));
	if (fd == NULL)
	{
		perror("malloc failed fd_create_fd_heredoc");
		return (NULL);
	}
	fd[0] = 1;
	fd[1] = fd_new;
	return (fd);
}

static int	*ft_fd_dup_add(int *fd, int fd_new)
{
	int	i;
	int	*fd_arr_new;

	fd_arr_new = (int *)malloc((fd[0] + 2) * sizeof(int));
	if (fd_arr_new == NULL)
		return (perror("malloc"), NULL);
	fd_arr_new[0] = fd[0] + 1;
	i = 0;
	while (++i <= fd[0])
		fd_arr_new[i] = fd[i];
	fd_arr_new[i] = fd_new;
	return (fd_arr_new);
}

//fd_new = -1 -> close all of other fds
//return (-1) -> malloc failed.
//-> call this func again with ft_fd_dup(-1);
// else return >= 0
int	ft_fd_dup(int fd_new)
{
	static int	*fd = 0;
	int			*fd_temp;
	int			i;

	if (fd == 0 && fd_new >= 0)
	{
		fd = ft_fd_dup_default(fd_new);
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
	fd_temp = ft_fd_dup_add(fd, fd_new);
	if (fd_temp == NULL)
		return (-1);
	return (free(fd), fd = fd_temp, fd_new);
}

int	ft_fd_out(int fd_new)
{
	static int	fd = -1;

	if (fd >= 0)
		close(fd);
	fd = fd_new;
	return (fd);
}
