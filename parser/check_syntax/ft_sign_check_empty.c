/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sign_check_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:49:02 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 00:37:29 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//1: gut
//2: not gut
static int	ft_check_empty_before2(char *str, int j, char *temp)
{
	if (str[j] == str[j - 1] && (str[j] == '|' || str[j] == '&'))
	{
		temp = ft_strndup(str + j - 1, 2);
		if (temp == 0)
			return (ft_printf_fd(2, "ft_strndup failed\n"), 0);
		return (ft_printf_fd(2, "systax error near `%s'\n", temp),
			free(temp), 0);
	}
	return (ft_printf_fd(2, "systax error near `%c'\n", str[j]), 0);
}

static int	ft_check_empty_before(char *str, int i, int j, char *temp)
{
	if (i == 0)
		return (1);
	if (str[i] == str[i - 1])
		i--;
	while (--i >= 0)
	{
		if (ft_isempty(str[i]) != 1)
		{
			if ((str[i] == '|') || (str[i] == '&' && str[i - 1] == '&')
				|| str[i] == '(')
			{
				if (str[j] == str[j - 1] && (str[j] == '|' || str[j] == '&'))
				{
					temp = ft_strndup(str + j - 1, 2);
					if (temp == 0)
						return (ft_printf_fd(2, "ft_strndup failed\n"), 0);
					return (ft_printf_fd(2, "systax error near `%s'\n", temp),
						free(temp), 0);
				}
				return (ft_printf_fd(2, "systax error near `%c'\n", str[j]), 0);
			}
			return (1);
		}
	}
	return (ft_check_empty_before2(str, j, temp));
}

static int	ft_check_empty_after2(char *str, int j, char *temp)
{
	if (str[j] == str[j - 1] && (str[j] == '|' || str[j] == '&'))
	{
		temp = ft_strndup(str + j - 1, 2);
		if (temp == 0)
			return (ft_printf_fd(2, "ft_strndup failed\n"), 0);
		return (ft_printf_fd(2, "systax error near `%s'\n", temp),
			free(temp), 0);
	}
	return (ft_printf_fd(2, "systax error near `%c'\n", str[j]), 0);
}

static int	ft_check_empty_after(char *str, int i)
{
	int		j;
	char	*temp;
// printf("%s\n", str + i);
	j = i;
	while (str[i] && str[++i])
	{
		if (ft_isempty(str[i]) != 1)
		{
			if ((str[i] == '|') || (str[i] == '&' && str[i - 1] == '&')
				|| str[i] == ')')
			{
				if (str[i] == str[i + 1] && (str[i] == '|' || str[i] == '&'))
				{
					temp = ft_strndup(str + i, 2);
					if (temp == 0)
						return (ft_printf_fd(2, "ft_strndup failed\n"), 0);
					return (ft_printf_fd(2, "systax error near `%s'\n", temp),
						free(temp), 0);
				}
				return (ft_printf_fd(2, "systax error near `%c'\n", str[i]), 0);
			}
		}
		return (1);
	}
	return (ft_check_empty_after2(str, j, 0));
}

int	ft_sign_check_empty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		if ((str[i] == '|' ) || (str[i + 1] == '&' && str[i] == '&'))
		{printf("%s\n", str + i);
			if ((str[i] == '|' && str[i + 1] == '|')
				|| ((str[i]) == '&' && str[i + 1] == '&'))
				i++;
			if (ft_check_empty_before(str, i, i, 0) == 0
				|| ft_check_empty_after(str, i) == 0)
				return (0);
		}
	}
	return (1);
}
