/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_check_uniq.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 09:22:27 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 17:57:38 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_count_valid_characters_of_a_word(char *str)
{
	int	i;

	i = 0;
	if (str == 0 || ft_isdigit(str[0]) == 1)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			i++;
		else
			return (i);
	}
	return (0);
}


// the redirection properly -> has name and sign => return (1)
// only redirection sign or not propername or reach the end of the line
// -> return (-1);
int	ft_skip_redirection(char *str)
{
	int	i;
	int	temp;

	i = 0;
	if (str[0] == str[1])
		i++;
	while (str[++i])
	{
		if (ft_isempty(str[i] != 1))
		{
			temp = ft_count_valid_characters_of_a_word(str + i);
			if (temp == 0)
				return (-1);
			return (i + temp);
		}
	}
	return (-1);
}

int	ft_print_str_error(char *str, int i)
{
	int		j;
	char	*temp;

	i = -1;
	if ((str[0] == '>' || str[0] == '<' ))
	{
		i++;
		if (str[0] == str[1])
			i++;
	}
	while (str[++i])
	{
		if (ft_isempty(str[i]) != 1)
		{
			j = i;
			while (ft_isalnum(str[i] == 1 || str[i] == '_'))
				i++;
			temp = ft_strndup(str + j, i - j + 1);
			if (temp == 0)
				return (ft_printf_fd(2, "malloc failed\n"), 0);
			return (ft_printf_fd(2, "syntax error `%s'\n",
					temp), free(temp), 0);
		}
	}
	return (0);
}

// == 1 => there is sign right after or at the end of line
// && there is no sign at all
// or only proper redirections there -> safe
// == 0 =>  there is something wrong.
int	ft_find_sign_after(char *str, int i)
{
	int	len;

	len = ft_strlen(str);
	while (++i < len)
	{
		if (str[i] == '|' || (str[i] == '&' && i + 1 <= len && str[i] == '&'))
			return (1);
		else if (ft_isempty(str[i]) != 1)
		{
			if (str[i] == '<' || str[i] == '>')
			{
				if (ft_skip_redirection(str + i) != -1)
					return (ft_print_str_error(str + i, -1));
				i = i + ft_skip_redirection(str + i);
			}
			else
				return (ft_print_str_error(str + i, -1));
		}
	}
	return (1);
}

// == 1 => there is sign right before. => syntax error only depends on after_arg
// or there is nothing before
// == 0 -> there is words before that -> error. for example aa (da    s)
int	ft_find_sign_before(char *str, int i)
{
	int		j;
	char	*temp;

	j = i + 1;
	while (--i >= 0)
	{
		if (str[i] == '|' || (str[i] == '&' && i >= 1 && str[i - 1] == '&'))
			return (1);
		else if (ft_isempty(str[i]) != 1)
		{
			while (ft_isempty(str[j]) == 1)
				j++;
			i = j;
			while (ft_isalnum(str[i] == 1 || str[i] == '_'))
				i++;
			temp = ft_strndup(str + j, i - j + 1);
			if (temp == 0)
				return (ft_printf_fd(2, "malloc failed\n"), 0);
			return (ft_printf_fd(2, "syntax error `%s'\n",
					temp), free(temp), 0);
		}
	}
	return (1);
}

// int	ft_parenthesis_check_uniq(char *str)
// {
// 	int	i;
// 	int	temp;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 			i = ft_strchr(str + i + 1, str[i]) - str;
// 		else if (str[i] == '(')
// 		{
// 			temp = ft_parenthesis_close_find(str + i + 1);
// 			if (ft_find_sign_before(str, i) == 0
// 				|| ft_find_sign_after(str, i + temp) == 0)
// 				return (0);
// 			i += temp;
// 		}
// 	}
// 	return (1);
// }

// int	main(void)
// {
// 	// char *str = "(22) | 1 | ( 2 && 144 ) && ( | ( )( )) || 2 ||(1) | 1";
// 	char *str = "((  || && |)1) ";

// 	if (ft_pre_check_input(str) == 0 || ft_parenthesis_check_uniq(str) == 0)
// 		ft_printf_fd(2, "somewere wrong\n");
// 	return (0);
// }
