/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:44:19 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 00:21:31 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(int ac, char **av, char **env)
{
	char 	*str1;
	char	*str2;
	char	*temp;
	char	**ret;
	int		i;

	if (ac == 1)
		return (printf("put input\n"), 0);
	str1 = ft_strdup(av[1]);
	i = 1;
	while (av[++i])
	{
		temp = str1;
		str2 = ft_strdup(av[i]);
		str1 = ft_strjoin(str2, temp);
		free(temp);
		free(str2);
	}
	str2 = dollar_handler(str1, env);
	// printf("str2 = {%s}\n", str2);
	ret = wc_expand(str2);
	i = 0;
	while (ret[i])
		printf("%s\n", ret[i++]);
	free(str1);
	free(str2);
	free_split(ret);
	ret = 0;
	str1 = 0;
	str2 = 0;
	// system("leaks mini");
	return(0);
}
