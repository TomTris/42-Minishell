/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_check_uniq2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:57:04 by qdo               #+#    #+#             */
/*   Updated: 2024/05/10 14:15:23 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_parenthesis_check_uniq(char *str)
{
	int	i;
	int	temp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		else if (str[i] == '(')
		{
			temp = ft_parenthesis_close_find(str + i + 1);
			if (ft_find_sign_before(str, i) == 0
				|| ft_find_sign_after(str, i + temp) == 0)
				return (0);
		}
	}
	return (1);
}
