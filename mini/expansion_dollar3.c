/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_dollar3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:00:36 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:43:44 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

//f_add free ori, return ret.
char	*f_add(char *ori, char *to_add, int n)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	len = ft_strlen(ori);
	ret = (char *)malloc((len + n + 1));
	if (ret == 0)
		return (exit_code(1), free(ori), perror("Malloc failed\n"), NULL);
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
		return (exit_code(1), perror("Malloc failed"), NULL);
	ret[0] = '$';
	ret[1] = 0;
	return (ret);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*str;
// 	char	**str2;
// ac = 0;
// av = 0;
// 	str = ft_strdup("");
// 	str = dollar_handler2("aaa$AAA..?.$BA\"$AAA\'$AAA\'\"", str, env);
// 	str2 = ft_split_after_dollar_expansion(str);
// 	free(str);
// 	while(str2[ac] != 0)
// 	{
// 		printf("%s\n", str2[ac++]);
// 	}
// 	str2 = ft_del_quo(str2);
// 	free_split(str2);
// 	str2 = 0;
// 	system("leaks a.out");
// 	str = 0;
// 	return (0);
// }
