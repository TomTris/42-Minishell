/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input5_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:23:32 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:34:16 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_init_helper(int *fd_heredoc_ori, int *len)
{
	*fd_heredoc_ori = get_fd_heredoc_ori(-1);
	if (*fd_heredoc_ori == -1)
		return (perror("sthwrong in ft_fd_heredoc_new"), 0);
	*len = 0;
	return (1);
}

int	ft_512(char *temp)
{
	if (print_fd(2, "Can't store more than 512 bytes, force") == -1
		|| print_fd (2, " break and keep doing execution!\n") == -1)
		return (exit_code(1), perror("printf_fd"), free(temp), 0);
	return (free(temp), 1);
}
