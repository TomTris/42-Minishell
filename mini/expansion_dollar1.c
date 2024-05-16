/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:13:05 by qdo               #+#    #+#             */
/*   Updated: 2024/05/15 14:16:16 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*dollar_doquo(char *str, char *ret, char **env, int *i)
{
	ret = f_add(ret, "\"", 1);
	if (ret == 0)
		return (NULL);
	ret = dollar_doquo2(str, ret, env, i);
	if (ret == 0)
		return (NULL);
	*i += 1;
	ret = f_add(ret, "\"", 1);
	return (ret);
}

char	*dollar_siquo(char *str, char *ret, int *i)
{
	int		j;

	j = *i - 1;
	*i += ft_strchr(str + *i, '\'') - str - *i + 1;
	ret = f_add(ret, str + j, *i - j);
	return (ret);
}

// $, "  or '
char	*dollar_handler3(char *str, char *ret, char **env, int *i)
{
	*i = *i + 1;
	if (str[*i - 1] == '$')
		return (dollar_out(str, ret, env, i));
	if (str[*i - 1] == '"')
		return (dollar_doquo(str, ret, env, i));
	return (dollar_siquo(str, ret, i));
}

char	*dollar_handler2(char *str, char *ret, char **env)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$' && str[i] != '"' && str[i] != '\'')
		{
			temp = ret;
			ret = snjoin(ret, str + i, 1);
			free(temp);
			if (ret == 0)
				return (perror("snjoin"), NULL);
			i++;
		}
		else
		{
			ret = dollar_handler3(str, ret, env, &i);
			if (ret == 0)
				return (NULL);
		}
	}
	return (ret);
}

// call this function -> no ambigious_0 anymore
char	**dollar_handler(char *str_ori, char **env)
{
	char	*str;
	char	**str2;

	str = ft_strdup("");
	if (str == 0)
		return (perror("ft_strdup"), NULL);
	str = dollar_handler2(str_ori, str, env);
	if (str == 0)
		return (NULL);
	str2 = ft_split_after_dollar_expansion(str);
	free(str);
	if (str2 == 0)
		return (NULL);
	str2 = ft_del_quo(str2);
	return (str2);
}
