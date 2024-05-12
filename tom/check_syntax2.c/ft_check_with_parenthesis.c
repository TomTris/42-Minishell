/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_with_parenthesis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 00:50:46 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 02:50:57 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// this file will check:
// if the parenthesis is uniq in that field?
// for example: 

// () a | bv -> in the filed of (), there is other stuff, which is not
// closed parenthesis nor re direction nor end of line nor other sign | || &&


//only | or && or || or (.
// good return 1, else 0.
int	ft_check_before(char *str, int i)
{
	char	*temp;
	int		j;

	j = i--;
	while (i >= 0)
	{
		if (ft_isempty(str[i] == 1))
			i--;
		else if (str[i] == '|' || (str[i] == '&' && str[i - 1] == '&')
			|| str[i] == '(')
			return (1);
		else
		{
			i = ft_count_valid_characters_of_a_word(str + j + 1);
			temp = ft_strndup(str + j, i);
			if (temp == 0)
				return (perror("Malloc failed\n"), 0);
			return (ft_printf_fd(2, "syntax error `%s'\n", temp),
				free(temp), 0);
		}
	}
	return (1);
}

//after redirection, must be alnum or _ or quotes.
//return value: good: >=0 => str[i] = the end of the redirection.
//0 -> bad.
int	ft_check_n_skip_redirection(char *str, int i)
{
	int	j;

	j = i++;
	if (str[i] == str[i + 1])
		i++;
	while (ft_isempty(str[i]) == 1)
		i++;
	if (ft_isalnum_(str[i]) == 1 || str[i] == '"' || str[i] == '\'')
	{
		if (str[i] == '"' || str[i] == '\'')
			return (ft_strchr(str + i + 1, str[i]) - str);
		while (ft_isalnum_(str[i]) == 1)
			i++;
		return (i - 1);
	}
	else
	{
		while (ft_isempty(str[i]) == 1)
			i++;
		return (0);
	}
}

// after (), only empty or | or || or && or redirections.
int	ft_check_after(char *str, int i)
{
	char	*temp;
	int		check;

	while (str[++i])
	{
		if (ft_isempty(str[i] != 1))
		{
			if (str[i] == '|' || (str[i] == '&' && str[i - 1] == '&')
				|| str[i] == ')')
				return (0);
			if (str[i] == '<' || str[i] == '>')
			{
				i = ft_skip_redirection(str, i);
				if (i == 0)
					return (0);
			}
		}
	}
	return (1);
}

int	ft_check_with_parenthesis(char *str)
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
			if (ft_check_before(str, i) == 0
				|| ft_check_after(str, i + temp) == 0)
				return (0);
		}
	}
	return (1);
}
