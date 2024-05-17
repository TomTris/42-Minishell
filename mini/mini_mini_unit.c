/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mini_unit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:28:07 by qdo               #+#    #+#             */
/*   Updated: 2024/05/17 01:54:37 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static t_mini_unit	*mini_unit_cre(int nbr, char ***env, int sign, int lvl)
{
	t_mini_unit	*ret;
	int			i;

	ret = (t_mini_unit *)malloc((nbr + 1) * sizeof(t_mini_unit));
	if (ret == 0)
		return (perror("malloc failed\n"), NULL);
	i = -1;
	while (++i <= nbr)
	{
		// ret[i].is_child = 0;
		ret[i].nbr = i;
		ret[i].nbr_sum = nbr;
		ret[i].lvl = lvl;
		ret[i].cmd = 0;
		ret[i].cmd = 0;
		ret[i].redi = 0;
		ret[i].fd_heredoc = 0;
		ret[i].env_ori = env;
		ret[i].sign_sub = sign;
		ret[i].mini = 0;
	}
	ret[0].nbr = nbr;
	return (ret);
}

static int	ft_cnt_mini_unit(char *str)
{
	int	i;
	int	i_old;
	int	sub;

	sub = 1;
	i = 0;
	i_old = i;
	while (str[i])
	{
		i += after_quote(str + i);
		i += after_mlt_parent(str + i);
		if (token(str + i) == PIPE)
		{
			sub++;
			i++;
		}
		if (i == i_old)
			i++;
		i_old = i;
	}
	return (sub);
}

static int	ft_pipe_finder(char *str)
{
	int	j;
	int	j_old;

	j = 0;
	j_old = j;
	while (str[j])
	{
		j += after_quote(str + j);
		j += after_mlt_parent(str + j);
		if (token(str + j) == PIPE)
			return (j);
		if (j == j_old)
			j++;
		j_old = j;
	}
	return (print_err
		("sth wrong in ft_pipe_finder,it go to the end of func\n"));
}

static int	ft_mini_unit_str_split(t_sub_mini *sub_mini)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (++i < sub_mini->mini_unit[0].nbr)
	{
		j = ft_pipe_finder(sub_mini->str);
		sub_mini->mini_unit[i].str = sndup(sub_mini->str, j);
		if (sub_mini->mini_unit[i].str == 0)
			return (print_err("sndup"));
		temp = sub_mini->str;
		sub_mini->str = ft_strdup(sub_mini->str + j + 1);
		free(temp);
		if (sub_mini->mini_unit[i].str == 0)
			return (print_err("ft_strdup"));
	}
	sub_mini->mini_unit[i].str = sub_mini->str;
	sub_mini->str = 0;
	return (1);
}

int	mini_unit0(t_sub_mini *sub_mini)
{
	int	cnt;
// printf("%d\n", sub_mini->lvl);
	cnt = ft_cnt_mini_unit(sub_mini->str);
	sub_mini->mini_unit = mini_unit_cre(cnt,
			sub_mini->env_ori, sub_mini->sign_after, sub_mini->lvl);
	if (sub_mini->mini_unit == 0)
		return (0);
	if (ft_mini_unit_str_split(sub_mini) == 0)
		return (0);
	cnt = 0;
	// while (++cnt <= sub_mini->mini_unit[0].nbr)
	// 	printf("sub_mini str = {%s}\n", sub_mini->mini_unit[cnt].str);
	cnt = 0;
	while (++cnt <= sub_mini->mini_unit[0].nbr)
	{
		if (syntax_check(&sub_mini->mini_unit[cnt],
				sub_mini->mini_unit[cnt].str) == 0)
		{
			// printf("mini_unit0 return\n");
			return (0);
		}
	}
	// cnt = 0;
	// while (++cnt <= sub_mini->mini_unit[0].nbr)
	// {
	// 	if (break_to_input(&sub_mini->mini_unit[cnt],
	// 			sub_mini->mini_unit[cnt].str) == 0)
	// 		return (0);
	// }
	return (1);
}
