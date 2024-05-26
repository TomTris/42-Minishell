/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:33:11 by qdo               #+#    #+#             */
/*   Updated: 2024/05/26 22:53:44 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
			return (exit_code(1), free_split(str2), perror("ftstrdup"), NULL);
		temp = ft_strdup(str2[i]);
		if (temp == 0)
			return (free_split(str2), free(ret), exit_code(1),
				perror("ft_strdup"), NULL);
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

static char	*empty_string(void)
{
	char	*ret;

	ret = (char *)malloc(1);
	if (ret == 0)
	{
		perror("malloc");
		exit_code(1);
	}
	else
		ret[0] = 0;
	return (ret);
}

char	*dollar_underscore(char **cmd, int only_return, int free_check)
{
	static char	*ret = NULL;
	int			i;

	if (ret == NULL)
		ret = empty_string();
	if (only_return == 1)
		return (ret);
	free(ret);
	ret = 0;
	if (free_check == 1)
		return (ret = 0, NULL);
	if (cmd == 0 || cmd[0] == 0)
		return (dollar_underscore(0, 1, 0));
	i = 0;
	while (cmd[i])
		i++;
	ret = ft_strdup(cmd[i - 1]);
	if (ret == 0)
		return (exit_code(1), perror("ret"), NULL);
	return (ret);
}

int	fft_isempty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isempty(str[i]) == 1)
			i++;
		else
			break ;
	}
	if (str[i] == 0)
		return (1);
	return (0);
}
