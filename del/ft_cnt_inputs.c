/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 05:22:06 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 07:00:31 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check from str[0] to the end, when find | / || / &&, return (1);
//else -> find something not empty -> return (0);
static int	ft_check_empty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isempty(str[i]) == 0)
			break ;
	}
	if (str[i] == 0 || str[i] == '|' || ft_strncmp(str + i, "&&", 2) == 0)
		return (1);
	return (0);
}

static int	ft_check_parenthesis_closed(char *str)
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
			i += ft_check_parenthesis_closed(str + i + 1);
	}
	return (write(2, "syntax error near unexpected token `('\n", 39), 0);
	return (0);
}

static int	ft_cnt_inputs2(char *str, int i, int sub_len, int check)
{
	int	z;

	z = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		else if (str[i] == ')')
			return (write(2, "syntax error: `)'\n", 18), 0);
		else if (str[i] == '(')
		{
			check = ft_check_parenthesis_closed(str + i + 1);
			if (check == 0)
				return (0);
			i += check;
		}
		if (ft_strncmp(str + i, "||", 2) == 0
			|| ft_strncmp(str + i, "&&", 2) == 0 || str[i] == '|')
		{
			sub_len++;
			if (ft_strncmp(str + i, "||", 2) == 0 || str[i] == '&')
			{
				check = 1;
				i++;
			}
			else
				check = 0;
			if (ft_check_empty(str + i + 1) == 1)
			{
				if (check == 1)
					i--;
				check = i + 1;
				if (str[check] != 0)
					while (str[++check])
						if (ft_isempty(str[check]) == 0)
							break ;
				if (str[check] == 0)
					check = i;
				if (str[check] == '&')
					return (write(2, "syntax error: `&&'\n", 19), 0);
				else if (str[check + 1] == '|')
					return (write(2, "syntax error: `||'\n", 19), 0);
				return (write(2, "syntax error: `|'\n", 18), 0);
			}
		}
	}
	return (sub_len);
}

//here pre-check quotes
int	ft_cnt_inputs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' || ft_strncmp(str + i, "&&", 2) == 0)
		{
			if (ft_check_empty(str) == 1)
			{
				if (str[i + 1] == '|')
					return (write(2, "syntax error: `||'\n", 19), 0);
				if (str[i] == '&')
					return (write(2, "syntax error: `&&'\n", 19), 0);
				return (write(2, "syntax error: `|'\n", 18), 0);
			}
		}
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (ft_strchr(str + i + 1, str[i]) == NULL)
			{
				if (write(2, "syntax error: invalid quote `", 29) >= 0)
					if (write(2, (void *)str + i, 1) > 0)
						write(2, "'\n", 2);
				return (0);

			}
			i = ft_strchr(str + i + 1, str[i]) - str;
		}
	}
	return (ft_cnt_inputs2(str, -1, 1, 0));
}

int	main(void)
{

	char	*str = " |( )";
	
	ft_cnt_inputs(str);
	// printf("%d\n", ft_cnt_inputs(str));
}
