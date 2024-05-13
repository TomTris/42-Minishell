/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:48:55 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 22:58:32 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	get_nbr(char *str)
{
	int	ret;
	int	i;

	ret = 1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ret)
		{
			i = -1;
			ret++;
		}
	}
	return (ret);
}

static void	ft_recovery(char **ret, int nbr)
{
	int	i;

	if (ret == 0 && ret[0] != 0)
		return ;
	i = -1;
	while (ret[0][++i])
		if (ret[0][i] == nbr)
			ret[0][i] = '*';
}

static char	*ft_dequo(char *str)
{
	int		i;
	char	**temp;
	char	*temp2;
	char	*ret;

	temp = ft_split(str, "\'\"");
	free(str);
	if (temp == 0)
		return (perror("ft_split"), NULL);
	ret = ft_strdup("");
	if (ret == 0)
		return (free_split(temp), perror("ft_strdup"), NULL);
	i = -1;
	while (temp[++i])
	{
		temp2 = ret;
		ret = ft_strjoin(ret, temp[i]);
		free(temp2);
		if (ret == 0)
			return (perror("ft_strjoin"), free_split(temp), NULL);
	}
	free_split(temp);
	return (ret);
}

char	**wc_expand(char *str_ori)
{
	char	**ret;
	int		i;
	char	*str;
	int		nbr;

	str = ft_strdup(str_ori);
	if (str == 0)
		return (perror("ft_strdup"), NULL);
	str = ft_dequo(str);
	if (str == 0)
		return (NULL);
	nbr = get_nbr(str_ori);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += ft_strchr(str + 1, str[i]) - str + 1;
		else if (str[i] == '*')
			str[i] = nbr;
		else
			i++;
	}
	ret = wc_expand2(str, nbr);
	ft_recovery(ret, nbr);
	return (free(str), ret);
}
