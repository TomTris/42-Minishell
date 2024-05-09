/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_check_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:07:58 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 12:13:58 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	ft_is_only_empty(char *str_start, char *str_end)
{
	if (str_end == 0)
	{
		while (*str_start)
			if (ft_isempty(*(str_start++)) == 0)
				return (0);
		return (1);
	}
	else if (str_end < str_start)
	{
		write(2, "something wrong in ft_is_only_empty\n", 36);
		return (1);
	}
	while (str_start <= str_end)
	{
		if (ft_isempty(*str_start) == 0)
			return (0);
		str_start++;
	}
	return (1);
}

static int	ft_check_quotes(char *str, int i, char *temp)
{
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			temp = ft_strchr(str + i + 1, '"');
			if (temp == 0)
				return (write(2,
						"syntax error near unexpected token `\"'\n", 39), 0);
			i = temp - str;
		}
		else if (str[i] == '\'')
		{
			temp = ft_strchr(str + i + 1, '\'');
			if (temp == 0)
				return (write(2,
						"syntax error near unexpected token `''\n", 39), 0);
			i = temp - str;
		}
	}
	return (1);
}

static int	ft_check_parenthesis_closed(char *str)
{
	int		i;
	int		check;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			i = ft_strchr(str + i + 1, '\'') - str;
		else if (str[i] == '"')
			i = ft_strchr(str + i + 1, '"') - str;
		else if (str[i] == ')')
			return (i);
		else if (str[i] == '(')
		{
			check = ft_check_parenthesis_closed(str + i + 1);
			if (check == 0)
				return (0);
			if (ft_is_only_empty(str + i + 1, str + i + 1 + check) == 1)
				return (write(2,
						"syntax error near unexpected token `)'\n", 39), 0);
			i = i + 1 + check;
		}
	}
	return (write(2, "syntax error near unexpected token `(`'\n", 39), 0);
}

static int	ft_check_parenthesis(char *str)
{
	int	i;
	int	check;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		else if (str[i] == ')')
			return (write(2,
					"syntax error near unexpected token `)'\n", 39), 0);
		else if (str[i] == '(')
		{
			check = ft_check_parenthesis_closed(str + i + 1);
			if (check == 0)
				return (0);
			i = i + 1 + check;
		}
	}
	return (1);
}

//quotes_unclosed_exit -> ctrl D -> exit -> exit code 127.
//command not found -> exit code 130
// || | => syntax error -> exit code 2
// () or (    ) or ||      -> exitcode 2- syntex
// because we don't handle unclosed quotes =>
//	if we get unclosed quotes or parenthesis, that's syntax error -> exit code 2

// here we checked: not unquoted, not unclosed parenthesis, not empty closed parenthesis.
int	ft_pre_check_input(char *str)
{
	if (ft_check_quotes(str, 0, 0) == 0 || ft_check_parenthesis(str) == 0)
	{
		printf("input not qualified\n");
		return (0);
	}
	return (1);
}

// int	main(void)
// {
// 	char *str = "(as'`'s)";

// 	if (ft_check_quotes(str, 0, 0) == 0 || ft_check_parenthesis(str) == 0)
// 	{
// 		printf("input not qualified\n");
// 		return (0);
// 	}
// 	return (1);
// }
