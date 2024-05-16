/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:52:32 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 18:42:55 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_cnt_line_heredoc(void)
{
	static int	cnt = 0;

	cnt ++;
	return (cnt);
}

//get-> call with -1
//set -> call with value
int	get_fd_heredoc_ori(int fd)
{
	static int	fd_heredoc = -1;

	if (fd != -1)
		fd_heredoc = fd;
	return (fd_heredoc);
}

int	ft_init_heredoc(t_mini *mini)
{
	unlink(HERE_DOC_FILE);
	mini->fd_heredoc = open(HERE_DOC_FILE, O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (mini->fd_heredoc == -1)
		return (perror("open"), ft_clean_programm(0, 1, 0), -99);
	get_fd_heredoc_ori(mini->fd_heredoc);
	return (1);
}
