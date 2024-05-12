/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isclosed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:07:58 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 01:17:34 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_is_unquoted(char *str)
{
	int		i;
	char	*temp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			temp = ft_strchr(str + i + 1, str[i]);
			if (temp == 0)
				return (print_err("invalid quotes!"));
			i = temp - str;
		}
	}
	return (1);
}

static int	ft_is_unparented(char *str, int ret, int cnt)
{
	int		i;
	char	*j;

	i = -1;
	cnt = 0;
	ret = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			j = ft_strchr(str + 1, str[i]);
			if (j == 0)
				return (print_err("invalid parenthesis!"));
			i += j - str;
		}
		if (str[i] == '(')
		{
			cnt++;
			ret++;
		}
		if (str[i] == ')')
			if (--cnt < 0)
				return (print_err("invalid parenthesis!"));
	}
	return (1);
}

int	ft_isclosed(char *str)
{
	if (ft_is_unquoted(str) == 0 || ft_is_unparented(str, 0, 0) == 0)
		return (0);
	return (1);
}
