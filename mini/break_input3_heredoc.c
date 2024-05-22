/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input3_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:49:25 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:33:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_fd_heredoc_new2(char *limiter, int write_end, int limi_len, int cnt)
{
	int		fd_heredoc_ori;
	char	*temp;
	int		len;

	if (ft_init_helper(&fd_heredoc_ori, &len) == 0)
		return (0);
	temp = readline(">");
	while (temp != 0
		&& (sncmp(limiter, temp, limi_len) != 1 || temp[limi_len] != '\0'))
	{
		len += ft_strlen(temp) + 1;
		if (len > 512)
			return (ft_512(temp));
		if (print_fd(fd_heredoc_ori, "%s\n", temp) == -1
			|| print_fd(write_end, "%s\n", temp) == -1)
			return (exit_code(1), perror("print_fd"), free(temp), 0);
		++cnt;
		ft_cnt_line_heredoc();
		free(temp);
		temp = readline(">");
	}
	if (temp == 0)
		if (ft_reach_end_of_file(limiter, cnt) == 0)
			return (0);
	return (free(temp), 1);
}

int	ft_fd_heredoc_new(char *limiter)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (exit_code(1), -1);
	if (ft_fd_heredoc(fd_pipe[0]) == -1)
	{
		exit_code(1),
		close (fd_pipe[0]);
		close (fd_pipe[1]);
		return (-1);
	}
	if (ft_fd_heredoc_new2(limiter, fd_pipe[1], ft_strlen(limiter), 0) == 0)
		return (close (fd_pipe[0]), close (fd_pipe[1]), -1);
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

char	*rm_dollar_before_quote(char *str, int i, char *ret)
{
	ret = ft_strdup("");
	if (ret == 0)
		return (exit_code(1), perror("ft_strdup"), free(str), NULL);
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
		return (exit_code(1), perror("sndup"), 0);
	ret = rm_dollar_before_quote(ret, 0, 0);
	if (ret == 0)
		return (0);
	temp = ft_strdup("");
	if (temp == 0)
		return (exit_code(1), free(ret), perror("ft_strdup"), 0);
	ret = ft_del_quo2(ret, temp);
	if (ret == 0)
		return (0);
	return (ft_heredoc_gen2(mini_unit, ret));
}
