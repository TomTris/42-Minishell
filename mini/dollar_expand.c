/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:36:11 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 22:36:21 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*make_dollar_sign(void)
{
	char	*ret;

	ret = (char *)malloc(2);
	if (ret == 0)
		return (perror("Malloc failed"), NULL);
	ret[0] = '$';
	ret[1] = 0;
	return (ret);
}

char	*dollar_replace(char *str, char **env, int *i)
{
	int		j;
	int		cnt;
	char	*temp;
	char	*ret;

	ret = sndup("", 0);
	cnt = 0;
	while (ft_isalnum_(str[*i]))
	{
		cnt++;
		*i = *i + 1;
	}
	temp = (char *)malloc(cnt + 1);
	if (temp == 0)
		return (perror("Malloc failed"), NULL);
	ft_strncpy(temp, str + *i - cnt, cnt);
	j = -1;
	cnt = ft_strlen(temp);
	while (env[++j])
	{
		if (sncmp(env[j], temp, cnt) == 1 && env[j][cnt] == '=')
		{
			ret = f_add(ret, env[j] + cnt + 1, ft_strlen(env[j] + cnt + 1));
			return (free(temp), ret);
		}
	}
	free(temp);
	return (ret);
}

char	*dollar_in(char *str, char **env, int *i)
{
	char	*temp;

	if (ft_isalnum_(str[*i]) != 1 || ft_isdigit(str[*i]) == 1 || str[*i] == 0)
	{
		temp = make_dollar_sign();
		return (temp);
	}
	temp = dollar_replace(str, env, i);
	return (temp);
}

char	*dollar_out(char *str, char *ret, char **env, int *i)
{
	char	*temp;

	if (str[*i] == '\'' || str[*i] == '"')
		return (ret);
	if (ft_isalnum_(str[*i]) != 1 || ft_isdigit(str[*i]) == 1 || str[*i] == 0)
	{
		temp = make_dollar_sign();
		if (temp == 0)
			return (free(ret), NULL);
		ret = f_add(ret, temp, 1);
		free(temp);
		return (ret);
	}
	temp = dollar_replace(str, env, i);
	if (temp == 0)
		return (free(ret), NULL);
	ret = f_add(ret, temp, ft_strlen(temp));
	free(temp);
	if (ret == 0)
		perror("ft_strjoin");
	return (ret);
}

char	*dollar_doquo2(char *str, char *ret, char **env, int *i)
{
	char	*temp;

	while (str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			*i += 1;
			temp = dollar_in(str, env, i);
			if (temp == 0)
				return (free(ret), NULL);
			ret = f_add(ret, temp, ft_strlen(temp));
			free(temp);
			if (ret == 0)
				return (ret);
		}
		else
		{
			ret = f_add(ret, str + *i, 1);
			if (ret == 0)
				return (ret);
			*i = *i + 1;
		}
	}
	return (ret);
}
