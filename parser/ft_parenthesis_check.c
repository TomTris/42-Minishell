/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 09:22:27 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 13:06:32 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_is_first_parenthe(char *str, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		else if (str[i] == '(')
			return (0);
	}
	return (1);
}

// == 1 => there is sign right before.
// == -1 -> first parenthesis, no words before
// == 0 -> there is words before that -> error
int	ft_find_sign_before(char *str, int i)
{
	int	j;

	j = i;
	while (--i >= 0)
	{
		if (str[i] == '|' || (str[i] == '&' && i >= 1 && str[i - 1] == '&'))
			return (1);
		else if (ft_isempty(str[i]) != 1)
			return (0);
	}
	return (-1);
}


// == 1 => there is sign right after
// == -1 => there is no sign at all.
// 
int	ft_find_sign_after(char *str, int j)
{
	int	len;

	len = ft_strlen(str);
	while (++j <= len)
	{
		if (str[j] == '|' || (str[j] == '&' && j + 1 <= len && str[j] == '&'))
			return (1);
		else if (ft_isempty(str[i]),)
	}
}

int	ft_check_uniq(char *str, int i, int j)
{
	int	k;

	ft_find_before();
	ft_find_sign_after();
	return (1);
}

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
			printf("i = %d, temp = %d\n", i, i + temp);
			if (ft_check_uniq(str, i, i + temp) == 0)
				return (0);
			printf("%d\n", temp);
			i += temp;
		}
	}
	return (1);
}

int	main(void)
{
	char *str = "(22) 1( 44 )(1)";

	if (ft_pre_check_input(str) == 0 || ft_parenthesis_check_uniq(str) == 0)
		ft_printf_fd(2, "somewere wrong\n");
	return (0);
}