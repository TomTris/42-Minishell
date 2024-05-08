/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_break.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:07:58 by qdo               #+#    #+#             */
/*   Updated: 2024/05/08 21:54:56 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *error, char *str)
{
	if (ft_strcmp(error, "syntax") == 1)
	{
		if (write(2, "syntax error near unexpected token `", 36) != -1)
			if (write(2, str, ft_strlen(str)) != -1)
				write(2, "'\n", 2);
	}
}

//str_end == 0 -> check til the end
int	ft_is_only_empty(char *str_start, char *str_end)
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


int	ft_check_parenthesis_closed(char *str)
{
	int		i;
	int		check;
	char	*temp;

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
				return (0);
			i = i + 1 + check;
		}
	}
	return (0);
}

int	ft_check_quotes(char *str, int i, char *temp)
{
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			temp = ft_strchr(str + i + 1, '"');
			if (temp == 0)
				return (ft_print_error("syntax", "\""), 0);
			i = temp - str;
		}
		else if (str[i] == '\'')
		{
			temp = ft_strchr(str + i + 1, '\'');
			if (temp == 0)
				return (ft_print_error("syntax", "'"), 0);
			i = temp - str;
		}
	}
	return (1);
}

int	ft_check_parenthesis(char *str)
{
	int	i;
	int	check;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			i = ft_strchr(str + i + 1, '\'') - str;
		else if (str[i] == '"')
			i = ft_strchr(str + i + 1, '"') - str;
		else if (str[i] == '(')
		{
			check = ft_check_parenthesis_closed(str + i + 1);
			if (check == 0)
				return (ft_print_error("syntax", "("), 0);
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
// char	**ft_input_break(char *str)

int	main(int ac, char **av)
{
	int	i;
	int	check;
	char	*str;

	if (ac == 1)
	{
		printf("put args\n");
		return (1);
	}
	str = av[1];
	printf("av = {%s}\n", str);
	if (ft_check_quotes(str, 0, 0) == 0 || ft_check_parenthesis(str) == 0)
	{
		printf("input not qualified\n");
	}
	else
		printf("good input\n");
	return (0);
}
