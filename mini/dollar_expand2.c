/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:00:36 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 22:42:59 by qdo              ###   ########.fr       */
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
