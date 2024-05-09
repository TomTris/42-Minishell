/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_break.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:15:50 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 05:48:23 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			i += ft_check_parenthesis_closed(str + i + 1);
		}
	}
	return (0);
}

static int	ft_ignore(char *str)
{
	int	i;

	i = 0;
	if (*str == '\'' || *str == '"')
		while (str[++i])
			if (str[i] == *str)
				return (i);
	return (ft_check_parenthesis_closed(str + 1));
}

int	main(int ac, char **av)
{
	char	*str = av[1];
	int		i;
	int		j;
	char	**input_break;

	if (ac == 1)
	{
		printf("put input\n");
		return (1);
	}
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (ft_strcmp(str + i, "||") == 0 || ft_strcmp(str + i, "&&") == 0
			|| str[i] == "|")
		{
			j++;
			if (str[i] != '|')
				i += 1;
		}
		else if (str[i] == '"' || str[i] == '\'' || str[i] == '(')
			i += ft_ignore(str + i);
	}
	input_break = (char **)malloc((j + 2) * sizeof(char *));
	if (input_break == 0)
		return (0);
	input_break
}


