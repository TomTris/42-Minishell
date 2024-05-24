/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mini_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 05:27:48 by qdo               #+#    #+#             */
/*   Updated: 2024/05/24 02:59:04 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	**make_env_empty2(char **ret, char *buf)
{
	char	*temp;

	ret = smerge(ret, "_=dv");
	if (ret == 0)
		return (exit_code(1), NULL);
	ret = smerge(ret, "SHLVL=1");
	if (ret == 0)
		return (exit_code(1), NULL);
	temp = ft_strjoin("PWD=", buf);
	if (temp == 0)
		return (free_split(ret), exit_code(1), NULL);
	ret = smerge(ret, temp);
	free(temp);
	if (ret == 0)
		exit_code(1);
	return (ret);
}

static char	**make_env_empty(void)
{
	char	**ret;
	char	buf[1024];
	int		i;

	i = -1;
	while (++i < 1024)
		buf[i] = 0;
	if (getcwd(buf, 1024) == NULL)
		return (exit_code(1), perror("getcwd"), NULL);
	ret = smerge(0, 0);
	if (ret == 0)
		return (exit_code(1), NULL);
	ret = smerge(ret, "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:"
			"/usr/local/munki:/Library/Apple/usr/bin");
	if (ret == 0)
		return (exit_code(1), perror("ft_split"), NULL);
	return (make_env_empty2(ret, buf));
}

static char	**modify_shlvl2(char **ret, int i)
{
	char	*temp;
	char	*temp2;
	int		nbr;

	nbr = ft_atoi(ret[i] + 6) + 1;
	if (nbr < 0)
		nbr = 0;
	temp = ft_itoa(nbr);
	if (temp == 0)
		return (exit_code(1), perror("ft_itoa"), free_split(ret), NULL);
	temp2 = temp;
	temp = ft_strjoin("SHLVL=", temp);
	free(temp2);
	if (temp == 0)
		return (exit_code(1), perror("ft_strjoin"), NULL);
	if (ft_env(&ret, temp, 1) == 0)
		return (free_split(ret), free(temp), NULL);
	return (ret);
}

static char	**modify_shlvl(char **ret)
{
	int		i;

	i = -1;
	while (ret[++i])
	{
		if (sncmp(ret[i], "SHLVL=", 6) == 1)
		{
			return (modify_shlvl2(ret, i));
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
		return (exit_code(1), NULL);
	i = -1;
	while (env[++i])
	{
		ret = smerge(ret, env[i]);
		if (ret == 0)
			return (exit_code(1), NULL);
	}
	return (modify_shlvl(ret));
}
