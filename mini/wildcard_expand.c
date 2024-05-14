/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:48:55 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 16:33:34 by qdo              ###   ########.fr       */
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

//free old ret and return new ret
static char	*ft_dequo2(char *str, char *ret, int *i)
{
	int		j;
	char	*temp;

	temp = ret;
	j = *i;
	if (str[j] == '\'')
	{
		(*i) += ft_strchr(str + j + 1, '\'') - str - j + 1;
		ret = snjoin(ret, str + j + 1, *i - j - 2);
	}
	else
	{
		ret = snjoin(ret, str + *i, 1);
		(*i)++;
	}
	free(temp);
	if (ret == 0)
		return (perror("snjoin"), NULL);
	return (ret);
}

//must free str and return ret
static char	*ft_dequo(char *str)
{
	int		i;
	int		j;
	char	*ret;
	char	*temp;

	ret = ft_strdup("");
	if (ret == 0)
		return (free(str), perror("ft_strdup"), NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			j = i;
			i += ft_strchr(str + i + 1, '\"') - str - i + 1;
			temp = ret;
			ret = snjoin(ret, str + j + 1, i - j - 2);
			free(temp);
			if (ret == 0)
				return (free(str), perror("snjoin"), NULL);
		}
		else
		{
			ret = ft_dequo2(str, ret, &i);
			if (ret == 0)
				return (free(str), NULL);
		}
	}
	free(str);
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
	str = ft_dequo(str);
	if (str == 0)
		return (NULL);
	ret = wc_expand2(str, nbr);
	ft_recovery(ret, nbr);
	return (free(str), ret);
}

int	main(void)
{
	int	i;
	char**ret;
	i = 0;

	ret = wc_expand("*");
	while (ret[i])
	{
		printf("%s ", ret[i]);
		i++;
	}
}