/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input4_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:52:32 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 21:06:20 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_fd_heredoc_add(t_mini_unit *mini_unit, int fd_new_to_add)
{
	int	i;
	int	j;
	int	*fd_new;

	if (mini_unit->fd_heredoc == NULL)
		i = 0;
	else
		i = mini_unit->fd_heredoc[0];
	fd_new = (int *)malloc((i + 2) * sizeof(int));
	if (fd_new == 0)
		return (0);
	if (i == 0)
		fd_new[0] = 1;
	else
		fd_new[0] = mini_unit->fd_heredoc[0] + 1;
	j = 0;
	while (++j <= i)
		fd_new[j] = mini_unit->fd_heredoc[j];
	fd_new[j] = fd_new_to_add;
	free(mini_unit->fd_heredoc);
	mini_unit->fd_heredoc = fd_new;
	return (1);
}

int	ft_reach_end_of_file(char *limiter)
{
	int	i;

	i = STDERR_FILENO;
	if (print_fd(i, "warning: here-document  ") == -1
		|| print_fd(i, "at line %d delimited", ft_cnt_line_heredoc()) == -1
		|| print_fd(i, " by end-of-file (wanted `%s')\n", limiter) == -1)
		return (perror("print_fd"), 0);
	return (1);
}

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
