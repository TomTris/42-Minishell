/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_precheck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:13:41 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 19:26:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//not free str
// ret[0] = 0 -> an empty string
// ret[0] == 2 -> $rggf -> abigious 
int	ft_ambigious(char *str) 
{
	int	i;

	if (str[0] != '$')
		return (0);
	if (ft_isdigit(str[1]) == 1 || ft_isalnum_(str[i + 1]) != 1)
		return (0);
	i = 2;
	while (str[i])
	{
		if (ft_isalnum_(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

static int	get_nbr(char *str)
{
	int	ret;
	int	i;

	ret = 1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ret)
		{
			i = -1;
			ret++;
		}
	}
	return (ret);
}

void	ft_change_star(char *str, int nbr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += ft_strchr(str + 1, str[i]) - str + 1;
		else if (str[i] == '*')
			str[i] = nbr;
		else
			i++;
	}
}
