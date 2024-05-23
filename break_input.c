/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:51:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/18 17:02:33 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	make_input_mini_unit2(t_mini_unit *mini_unit, char *str, int *i)
{
	if (token(str + *i) == HERE_DOC)
	{
		if (ft_heredoc_gen(mini_unit, str, i) == 0)
			return (0);
		return (1);
	}
	else if (token(str + *i) == APPEND
		|| token(str + *i) == RE_IN || token(str + *i) == RE_OUT)
	{
		if (ft_redi_gen(mini_unit, str, i, token(str + *i)) == 0)
			return (0);
		return (1);
	}
	else if (token(str + *i) == 0)
	{
		if (ft_cmd_gen(mini_unit, str, i) == 0)
			return (0);
		return (1);
	}
	return (print_err("sth wrong in make_input_mini_unit\n"));
}

int	make_input_mini_unit(t_mini_unit *mini_unit)
{
	int		i;
	char	*str;

	i = 0;
	str = mini_unit->str;
	while (str[i])
	{
		if (ft_isempty(str[i]) == 1)
			i++;
		else if (token(str + i) == O_PARENT)
		{
			if (make_input_mini(mini_unit->mini) == 0)
				return (0);
			i += after_1_parent(str + i);
		}
		else
		{
			if (make_input_mini_unit2(mini_unit, str, &i) == 0)
				return (0);
		}
	}
	return (1);
}

int	make_input_sub_mini(t_sub_mini *sub_mini)
{
	int	i;

	i = 0;
	while (++i <= sub_mini->mini_unit[0].nbr)
	{
		if (make_input_mini_unit(&(sub_mini->mini_unit[i])) == 0)
			return (0);
	}
	return (1);
}

int	make_input_mini(t_mini *mini)
{
	int	i;

	i = 0;
	while (++i <= mini->sub_mini[0].nbr)
	{
		if (make_input_sub_mini(&(mini->sub_mini[i])) == 0)
			return (0);
	}
	return (1);
}

int	break_input(t_mini *mini)
{
	if (make_input_mini(mini) == 0)
		return (0);
	return (1);
}
