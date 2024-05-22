/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mini_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 05:27:48 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 05:31:08 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	**make_env_empty(void)
{
	char	**ret;
	char	buf[1024];
	int		i;

	i = -1;
	while (++i < 1024)
		buf[i] = 0;
	if (getcwd(buf, 1024) == NULL)
		return (perror("getcwd"), NULL);
	ret = smerge(0, 0);
	if (ret == 0)
		return (NULL);
	ret = smerge(ret, "_=dv");
	if (ret == 0)
		return (NULL);
	ret = smerge(ret, "SHLVL=1");
	if (ret == 0)
		return (NULL);
	ret = smerge(ret, buf);
	return (ret);
}

static char	**modify_shlvl(char **ret)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = -1;
	while (ret[++i])
	{
		if (sncmp(ret[i], "SHLVL=", 6) == 1)
		{
			temp = ft_itoa(ft_atoi(ret[i] + 6) + 1);
			if (temp == 0)
				return (perror("ft_itoa"), free_split(ret), NULL);
			temp2 = temp;
			temp = ft_strjoin("SHLVL=", temp);
			free(temp2);
			if (temp == 0)
				return (perror("ft_strjoin"), NULL);
			if (ft_env(&ret, temp, 1) == 0)
				return (free_split(ret), free(temp), NULL);
			return (ret);
		}
	}
	if (ft_env(&ret, "SHLVL=1", 1) == 0)
		return (NULL);
	return (ret);
}

char	**make_env(char **env)
{
	char	**ret;
	int		i;

	if (env[0] == 0)
		return (make_env_empty());
	ret = smerge(0, 0);
	if (ret == 0)
		return (0);
	i = -1;
	while (env[++i])
	{
		ret = smerge(ret, env[i]);
		if (ret == 0)
			return (0);
	}
	return (modify_shlvl(ret));
}
