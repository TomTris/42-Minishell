/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frequent_used_func.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 09:23:55 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 22:19:55 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_trim_whitespace(char *str)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
		if (ft_isempty(str[i]) != 1)
			break ;
	if (str[i] == 0)
		return (ft_strdup(""));
	i = -1;
	while (str[++i])
		if (ft_isempty(str[i]) != 1)
			break ;
	j = ft_strlen(str);
	while (str[--j])
		if (ft_isempty(str[j]) != 1)
			break ;
	return (ft_strndup(str + i, j - i + 1));
}

int	ft_parenthesis_close_find(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		else if (str[i] == ')')
			return (i + 1);
		else if (str[i] == '(')
			i += ft_parenthesis_close_find(str + i + 1);
	}
	return (0);
}

int	ft_check_syntax(char *str)
{
	if (ft_pre_check_input(str) == 0 ||
		ft_parenthesis_check_uniq(str) == 0 || ft_sign_check_empty(str) == 0)
		return (0);
	return (1);
}
// char *str = "(22) | 1 | ( 2 && 144 ) && ( | ( )( )) || 2 ||(1) | 1";
// char *str = "((  1|  )1 |) ";
// char *str = "(1 |((1)) <1| (1) && 7 ) || a";
// char *str = "1 <baaa<323232";
// char *str;
// ac = 0;
// str = av[1];
//ls -l | wc -l | sleep 4 | cat <Makefile >  | cat