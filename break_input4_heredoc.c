/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input4_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 01:48:08 by qdo               #+#    #+#             */
/*   Updated: 2024/05/27 01:48:51 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_fd_heredoc_new3(int *len)
{
	char	*temp;

	signal(SIGINT, ft_sig_heredoc);
	ft_ctrl_c(0);
	*len = 0;
	if (isatty(STDIN_FILENO))
		temp = readline("> ");
	else
		temp = get_next_line(STDIN_FILENO);
	return (temp);
}

int	ft_fd_heredoc_new4(char *temp, char *limiter, int cnt)
{
	if (ft_ctrl_c(-1) == 1)
		return (ft_ctrl_c(0), free(temp), 0);
	if (temp == 0)
		if (ft_reach_end_of_file(limiter, cnt) == 0)
			return (0);
	return (free(temp), signal(SIGINT, sigint_handler2), 1);
}

int	ft_fd_heredoc_new2(char *limiter, int write_end, int limi_len, int cnt)
{
	char	*temp;
	int		len;

	temp = ft_fd_heredoc_new3(&len);
	while (temp != 0 && ft_ctrl_c(-1) == 0
		&& (sncmp(limiter, temp, limi_len) != 1 || temp[limi_len] != '\0'))
	{
		len += ft_strlen(temp) + 1;
		if (len > 512)
			return (ft_512(temp));
		if (print_fd(write_end, "%s\n", temp) == -1)
			return (exit_code(1), perror("print_fd"), free(temp), 0);
		++cnt;
		ft_cnt_line_heredoc();
		free(temp);
		if (isatty(STDIN_FILENO))
			temp = readline("> ");
		else
			temp = get_next_line(STDIN_FILENO);
	}
	return (ft_fd_heredoc_new4(temp, limiter, cnt));
}
