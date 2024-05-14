/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:00:36 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 22:10:33 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*f_add(char *ori, char *to_add, int n)
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

char	**ft_split_after_dollar_expansion3(char *str, char **ret, int *i, int j)
{
	char	*temp;

	if (j != 0)
	{
		temp = sndup(str + *i - j, j);
		if (temp == 0)
			return (perror("sndup"), free_split(ret), NULL);
		ret = smerge(ret, temp);
		free(temp);
	}
	return (ret);
}

char	**ft_split_after_dollar_expansion2(char *str, char **ret, int *i)
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
		return (0);
	i = 0;
	while (str[i])
	{
		ret = ft_split_after_dollar_expansion2(str, ret, &i);
		if (ret == 0)
			return (NULL);
	}
	return (ret);
}

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

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	**str2;
ac = 0;
av = 0;
	str = ft_strdup("");
	str = dollar_handler2("aaa$AAA...$BA\"$AAA\'$AAA\'\"", str, env);
	str2 = ft_split_after_dollar_expansion(str);
	free(str);
	str2 = ft_del_quo(str2);
	free_split(str2);
	str = 0;
	// system("leaks a.out");
	return (0);
}



// call this function -> no ambigious_0 anymore
// char	**dollar_handler(char *str_ori, char **env)
// {
// 	char	*str_ret;
// 	char	**ret;

// 	str_ret = dollar_handler1(str_ori, env);
// 	return (ft_split_after_dollar_expansion(str_ret));
// }
