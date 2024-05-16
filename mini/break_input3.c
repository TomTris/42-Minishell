/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:49:25 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 04:15:19 by qdo              ###   ########.fr       */
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

// do we need to closed the read end when we write into write end?
// so i need to fork, and child process will write into pipe.
int	ft_fd_heredoc_new2(char *limiter, int write_end)
{
	int		fd_heredoc_ori;
	char	*temp;
	int		temp_len;

	temp = get_next_line(STDIN_FILENO);
	temp_len = ft_strlen(temp);
	fd_heredoc_ori = get_fd_heredoc_ori(-1);
	if (fd_heredoc_ori == -1)
		return (perror("sthwrong in ft_fd_heredoc_new"), 0);
	while (temp != 0
		&&(sncmp(limiter, temp, temp_len) != 1 || temp[temp_len] != '\n'))
	{
		if (print_fd(fd_heredoc_ori, temp) == -1
			|| print_fd(write_end, temp) == -1)
				return (free(temp), 0);
		ft_cnt_line_heredoc();
		free(temp);
		temp = get_next_line(STDIN_FILENO);
	}
	if (temp == 0)
		if (ft_reach_end_of_file(limiter) == 0)
			return (free(temp), 0);
	free(temp);
	return (1);
}

int	ft_fd_heredoc_new(char *limiter)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (-1);
	if (ft_fd_heredoc_new2(limiter, fd_pipe[1]) == 0)
		return (close(fd_pipe[0]), -1);
	return (fd_pipe[0]);
}

int	ft_heredoc_gen(t_mini_unit *mini_unit, char *str, int *i)
{
	char	*ret;
	char	*temp;
	int		j;

	*i += 2;
	if (ft_isempty(str[*i]) == 1)
		*i += 1;
	j = ft_take_string(str, i);
	ret = sndup(str + *i - j, j);
	if (ret == 0)
		return (perror("sndup"), 0);
	temp = ft_strdup("");
	if (temp == 0)
		return (free(ret), perror("ft_strdup"), 0);
	ret = ft_del_quo2(ret, temp);
	if (ret == 0)
		return (0);
	j = ft_fd_heredoc_new(ret);
	free(ret);
	if (j == -1)
		return (0);
	if (ft_fd_heredoc_add(mini_unit, j) == 0)
		return (0);
	return (1);
}
