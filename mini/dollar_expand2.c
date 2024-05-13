/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:13:05 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 00:30:13 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//must free str, cause it's created when this func is called
static char	*ft_rpl(char *str, char **env)
{
	int	i;
	int	len;

	if (str == 0)
		return (perror("ft_strndup"), NULL);
	len = ft_strlen(str);
	i = 0;
	while (env[i])
	{
		if (sncmp(str, env[i], len) && env[i][len] == '=')
		{
			free(str);
			str = ft_strdup(env[i] + len + 1);
			if (str == 0)
				return (perror("ft_strdup"), NULL);
			return (str);
		}
		i++;
	}
	free(str);
	str = ft_strdup("");
	if (str == 0)
		return (perror("ft_strdup"), NULL);
	return (str);
}

//str[0] = '$'
// don't free str
static char	*dl_1_replace(char *str, char **env)
{
	char	*ret;

	if ((ft_isdigit(str[1]) == 1)
		|| (ft_isalnum_(str[1]) != 1 && str[1] != '\'' && str[1] != '"'))
	{
		ret = (char *)malloc(2 * sizeof(char));
		if (ret == 0)
			return (perror("Malloc failed"), NULL);
		ret[0] = '$';
		ret[1] = 0;
		return (ret);
	}
	else
		return (ft_rpl(sndup(str + 1, after_1_dollar(str) - 1), env));
}

//must free ori
static char	*f_add(char *ori, char *to_add, int n)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	len = ft_strlen(ori);
	ret = (char *)malloc((len + n + 1));
	if (ret == 0)
		return (free(ori), perror("Malloc failed\n"), NULL);
	i = -1;
	while (ori[++i])
		ret[i] = ori[i];
	j = -1;
	while (++j < n)
		ret[i++] = to_add[j];
	ret[i] = 0;
	free(ori);
	return (ret);
}


char	*ft_is_dollar(char *ret, char *str, int i, char **env)
{
	char	*temp;
	char	*temp2;

	temp = dl_1_replace(str + i, env);
	if (temp == 0)
		return (free(ret), NULL);
	temp2 = ret;
	ret = ft_strjoin(ret, temp);
	free(temp2);
	free(temp);
	if (ret == 0)
		return (perror("ft_strjoin"), NULL);
	return (ret);
}

char	*ft_isnt_dollar(char *str, char *ret, int *i)
{
	int	j;

	j = *i;
	if (str[*i] == '\'')
		*i += ft_strchr(str, str[*i]) - str + 1;
	else if (str[*i] != '$')
		(*i)++;
	ret = f_add(ret, str + j, *i - j);
	return (ret);
}
