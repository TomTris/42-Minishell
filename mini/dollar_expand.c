/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:00:36 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 00:06:55 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//no free.
int	after_1_dollar(char *str)
{
	int	i;

	if (str[0] != '$')
		return (0);
	if (ft_isdigit(str[1]) == 1 || ft_isalnum_(str[1]) != 1)
		return (1);
	i = 2;
	while (ft_isalnum_(str[i]) == 1 && str[i] != 0)
		i++;
	return (i);
}

// must return ret, but only ret.
static char	*ft_dollar_expand(char *str, char *ret, char **env)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ret = ft_is_dollar(ret, str, i, env);
			i += after_1_dollar(str + i);
		}
		else
		{
			ret = ft_isnt_dollar(str, ret, &i);
			if (ret == 0)
				return (NULL);
		}
	}
	return (ret);
}

char	*dollar_handler(char *str_ori, char **env)
{
	char	*str;
	char	*ret;

	str = ft_strdup(str_ori);
	if (str == 0)
		return (perror("ft_strdup"), NULL);
	ret = ft_strdup("");
	if (ret == 0)
		return (perror("ft_strdup"), free(str), NULL);
	ret = ft_dollar_expand(str, ret, env);
	free(str);
	if (ret == 0)
		return (NULL);
	return (ret);
}
