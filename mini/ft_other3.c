/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:33:11 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 18:40:28 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//free both str2_i and ret, f_add free ret, ft_del_quo2 free(str2_i).
//return the value of a "quote deleted string"
//ret should be ""
char	*ft_del_quo2(char *str2_i, char *ret)
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

//create ret = "" before call ft_del_quo2
char	**ft_del_quo(char **str2)
{
	int		i;
	char	*temp;
	char	*ret;

	i = 0;
	while (str2[i])
	{
		ret = ft_strdup("");
		if (ret == 0)
			return (free_split(str2), perror("ft_strdup"), NULL);
		temp = ft_strdup(str2[i]);
		if (temp == 0)
			return (free_split(str2), free(ret), perror("ft_strdup"), NULL);
		temp = ft_del_quo2(temp, ret);
		if (temp == 0)
		{
			free_split(str2);
			return (NULL);
		}
		free(str2[i]);
		str2[i] = temp;
		i++;
	}
	return (str2);
}
