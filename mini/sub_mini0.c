/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_mini0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 05:15:05 by qdo               #+#    #+#             */
/*   Updated: 2024/05/12 10:42:57 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_cnt_sub_mini(char *str)
{
	int	i;
	int	i_old;
	int	sub;

	i = 0;
	i_old = i;
	sub = 1;
	while (str[i])
	{
		i += after_quote(str + i);
		i += after_mlt_parent(str + i);
		if (token(str + i) == OR || token(str + i) == AND)
		{
			i++;
			sub++;
		}
		if (i == i_old)
			i++;
		i_old = i;
	}
	return (sub);
}

static t_sub_mini	*sub_mini_cre(int nbr, char ***env)
{
	t_sub_mini	*ret;
	int			i;

	ret = (t_sub_mini *)malloc((nbr + 1) * sizeof(t_sub_mini));
	if (ret == 0)
		return (perror("Malloc failed\n"), NULL);
	i = -1;
	while (++i < nbr)
	{
		ret[i].nbr = 0;
		ret[i].str = 0;
		ret[i].sign_after = 0;
		ret[i].env_ori = env;
		ret[i].mini_unit = 0;
		ret[i].str = 0;
	}
	ret[0].nbr = nbr;
	return (ret);
}

static int	ft_or_and_finder(t_sub_mini *sub_mini, char *str)
{
	int	i;

	i = -1;
	while (str[i])
	{
		if (token(str + i) != OR && token(str + i) != AND)
			i++;
		i += after_quote(str + i);
		i += after_mlt_parent(str + i);
		if (token(str + i) == OR || token(str + i) == AND)
		{
			sub_mini->sign_after = token(str + 1);
			return (i);
		}
	}
	return (print_err("sth wrong in ft_init_sub_mini2\n"));
}

static int	ft_init_sub_mini(t_sub_mini	*sub_mini, char *str_ori)
{
	char	*str;
	int		i;
	int		j;
	char	*temp;

	str = ft_strdup(str_ori);
	if (str == 0)
		return (perror("ft_strdup"), 0);
	i = 0;
	while (++i < sub_mini[0].nbr)
	{
		temp = str;
		j = ft_or_and_finder(&sub_mini[i], str);
		sub_mini[i].str = sndup(str, j);
		if (sub_mini[i].str == 0)
			return (perror("sndup"), free(temp), 0);
		str = ft_strdup(str + j + 2);
		free(temp);
		if (str == 0)
			return (perror("ft_strdup"), 0);
	}
	sub_mini[i].str = str;
	return (1);
}

int	sub_mini0(t_mini *mini)
{
	int	i;

	mini->str = mini->str;
	mini->sub_mini = sub_mini_cre(ft_cnt_sub_mini(mini->str), &mini->env);
	if (mini->sub_mini == NULL)
		return (0);
	if (ft_init_sub_mini(mini->sub_mini, mini->str) == 0)
		return (ft_free_mini(mini), 0);
	i = 0;
	while (++i <= mini->sub_mini[0].nbr)
	{
		if (mini_unit0(&mini->sub_mini[i]) == 0)
			return (ft_free_sub_mini(&mini->sub_mini));
	}
	return (1);
}
