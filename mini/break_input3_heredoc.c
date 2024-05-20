/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input3_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:49:25 by qdo               #+#    #+#             */
/*   Updated: 2024/05/19 20:47:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_fd_heredoc_new2(char *limiter, int write_end)
{
	int		fd_heredoc_ori;
	char	*temp;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	fd_heredoc_ori = get_fd_heredoc_ori(-1);
	if (fd_heredoc_ori == -1)
		return (perror("sthwrong in ft_fd_heredoc_new"), 0);
	temp = get_next_line(STDIN_FILENO);
	while (temp != 0
		&& (sncmp(limiter, temp, limiter_len) != 1
			|| temp[limiter_len] != '\n'))
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
			return (0);
	free(temp);
	return (1);
}

int	ft_fd_heredoc_new(char *limiter)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (-1);
	if (ft_fd_heredoc(fd_pipe[0]) == -1)
	{
		close (fd_pipe[0]);
		close (fd_pipe[1]);
		return (-1);
	}
	if (ft_fd_heredoc_new2(limiter, fd_pipe[1]) == 0)
		return (close (fd_pipe[0]), close (fd_pipe[1]), -1);
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

char	*rm_dollar_before_quote(char *str, int i, char *ret)
{
	ret = ft_strdup("");
	if (ret == 0)
		return (perror("ft_strdup"), free(str), NULL);
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else if (str[i] == '"' || str[i] == '\'')
		{
			ret = f_add(ret, str + i,
					ft_strchr(str + i + 1, str[i]) - str - i + 1);
			if (ret == 0)
				return (perror("ft_strdup"), free(str), NULL);
			i += ft_strchr(str + i + 1, str[i]) - str - i + 1;
		}
		else
		{
			ret = f_add(ret, str + i, 1);
			if (ret == 0)
				return (perror("ft_strdup"), free(str), NULL);
			i++;
		}
	}
	free(str);
	return (ret);
}

static int	ft_heredoc_gen2(t_mini_unit *mini_unit, char *ret)
{
	int	j;

	j = ft_fd_heredoc_new(ret);
	free(ret);
	if (j == -1)
		return (0);
	if (ft_fd_heredoc_add(mini_unit, j) == 0)
		return (0);
	return (1);
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
	ret = rm_dollar_before_quote(ret, 0, 0);
	if (ret == 0)
		return (0);
	temp = ft_strdup("");
	if (temp == 0)
		return (free(ret), perror("ft_strdup"), 0);
	ret = ft_del_quo2(ret, temp);
	if (ret == 0)
		return (0);
	return (ft_heredoc_gen2(mini_unit, ret));
}
