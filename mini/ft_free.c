/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 07:14:59 by qdo               #+#    #+#             */
/*   Updated: 2024/05/12 09:11:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	free_split(char **to_free2)
{
	int	i;

	if (to_free2 != 0)
	{
		i = -1;
		while (to_free2[++i])
			free(to_free2[i]);
		free(to_free2);
	}
	return (0);
}

int	ft_free_mini_unit(t_mini_unit **mini_unit_ori)
{
	t_mini_unit	*mini_unit;

	mini_unit = *mini_unit_ori;
	free(mini_unit->cmd);
	free_split(mini_unit->append);
	free_split(mini_unit->args);
	free_split(mini_unit->here_doc);
	free_split(mini_unit->re_in);
	free_split(mini_unit->re_out);
	free_split(mini_unit->append);
	free(mini_unit);
	*mini_unit_ori = 0;
	return (0);
}

int	ft_free_sub_mini(t_sub_mini **sub_mini_ori)
{
	int			i;
	t_sub_mini	*sub_mini;

	i = 0;
	sub_mini = *sub_mini_ori;
	free(sub_mini->str);
	while (++i <= sub_mini->mini_unit[0].nbr)
		ft_free_mini_unit(&sub_mini[i].mini_unit);
	free(*sub_mini_ori);
	*sub_mini_ori = 0;
	return (0);
}

int	ft_free_mini(t_mini *mini)
{
	int			i;

	i = 0;
	free(mini->str);
	while (++i <= mini->sub_mini[0].nbr)
		ft_free_sub_mini(&mini[i].sub_mini);
	return (0);
}

