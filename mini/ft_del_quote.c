/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:33:11 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 23:37:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*ft_del_quo2(char *str2_i, char *ret)
{
	int		j;
	int		k;

	j = 0;
	while (str2_i[j])
	{
		if (str2_i[j] != '"' && str2_i[j] != '\'')
		{
			ret = f_add(ret, str2_i + j, 1);
			if (ret == 0)
				return (free(str2_i), perror("ft_strdup"), NULL);
			j++;
		}
		else
		{
			k = ft_strchr(str2_i + j + 1, str2_i[j]) - str2_i - j + 1;
			j += ft_strchr(str2_i + j + 1, str2_i[j]) - str2_i - j + 1;
			ret = f_add(ret, str2_i + j - k + 1, k - 2);
			if (ret == 0)
				return (free(str2_i), NULL);
		}
	}
	free(str2_i);
	return (ret);
}

char	**ft_del_quo(char **str2)
{
	int		i;
	char	*ret;

	i = 0;
	while (str2[i])
	{
		ret = ft_strdup("");
		if (ret == 0)
			return (free_split(str2), perror("ft_strdup"), NULL);
		str2[i] = ft_del_quo2(str2[i], ret);
		if (str2[i] == 0)
		{
			free_split(str2);
			return (NULL);
		}
		i++;
	}
	return (str2);
}
