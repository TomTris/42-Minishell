/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 07:14:59 by qdo               #+#    #+#             */
/*   Updated: 2024/05/27 01:12:12 by qdo              ###   ########.fr       */
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

static void	free_mini_unit_redi(t_redirection *redi)
{
	int	i;

	i = 0;
	if (redi != 0)
	{
		while (++i <= redi[0].type_re)
		{
			free(redi[i].str);
		}
		free(redi);
	}
}

static int	free_mini_unit(t_mini_unit *mini_unit)
{
	int	i;

	i = 0;
	while (++i <= mini_unit[0].nbr)
	{
		free(mini_unit[i].str);
		free_split(mini_unit[i].cmd);
		free_mini_unit_redi(mini_unit[i].redi);
		free(mini_unit[i].fd_heredoc);
		if (mini_unit[i].mini != 0)
		{
			free_mini(mini_unit[i].mini);
			free(mini_unit[i].mini);
		}
	}
	free(mini_unit);
	return (0);
}

static int	free_sub_mini(t_sub_mini *sub_mini)
{
	int			i;

	i = 0;
	while (++i <= sub_mini[0].nbr)
	{
		free(sub_mini[i].str);
		if (sub_mini[i].mini_unit != 0)
			free_mini_unit(sub_mini[i].mini_unit);
	}
	free(sub_mini);
	return (0);
}

int	free_mini(t_mini *mini)
{
	free(mini->str);
	free_sub_mini(mini->sub_mini);
	return (0);
}
