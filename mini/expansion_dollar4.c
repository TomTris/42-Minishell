/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_dollar4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:33:55 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:44:10 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	**ft_split_after_dollar_expansion3(char *str,
		char **ret, int *i, int j)
{
	char	*temp;

	if (j != 0)
	{
		temp = sndup(str + *i - j, j);
		if (temp == 0)
			return (exit_code(1), perror("sndup"), free_split(ret), NULL);
		ret = smerge(ret, temp);
		free(temp);
	}
	return (ret);
}

static char	**ft_split_after_dollar_expansion2(char *str, char **ret, int *i)
{
	int		j;

	while (ft_isempty(str[*i]) == 1)
		*i += 1;
	j = 0;
	while (str[*i] && ft_isempty(str[*i]) != 1)
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			j += ft_strchr(str + *i + 1, str[*i]) - str - *i + 1;
			*i += ft_strchr(str + *i + 1, str[*i]) - str - *i + 1;
		}
		else
		{
			(*i)++;
			j++;
		}
	}
	return (ft_split_after_dollar_expansion3(str, ret, i, j));
}

char	**ft_split_after_dollar_expansion(char *str)
{
	int		i;
	char	**ret;

	ret = smerge(0, 0);
	if (ret == 0)
		return (exit_code(1), 0);
	i = 0;
	while (str[i])
	{
		ret = ft_split_after_dollar_expansion2(str, ret, &i);
		if (ret == 0)
			return (NULL);
	}
	return (ret);
}
