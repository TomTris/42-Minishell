/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input4_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:52:32 by qdo               #+#    #+#             */
/*   Updated: 2024/05/27 01:35:48 by qdo              ###   ########.fr       */
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
		return (exit_code(1), 0);
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

int	ft_reach_end_of_file(char *limiter, int cnt)
{
	int	i;

	i = STDERR_FILENO;
	if (print_fd(i, "warning: here-document  ") == -1
		|| print_fd(i, "at line %d delimited",
			ft_cnt_line_heredoc() - cnt) == -1
		|| print_fd(i, " by end-of-file (wanted `%s')\n", limiter) == -1)
		return (exit_code(1), perror("print_fd"), 0);
	return (1);
}

int	ft_cnt_line_heredoc(void)
{
	static int	cnt = 0;

	cnt ++;
	return (cnt);
}

int	ft_512(char *temp)
{
	if (print_fd(2, "Can't store more than 512 bytes, force") == -1
		|| print_fd (2, " break and keep doing execution!\n") == -1)
		return (exit_code(1), perror("printf_fd"), free(temp), 0);
	return (free(temp), 1);
}

int	ft_ctrl_c(int nbr)
{
	static int	ret = 0;

	if (nbr >= 0)
		ret = nbr;
	return (ret);
}
