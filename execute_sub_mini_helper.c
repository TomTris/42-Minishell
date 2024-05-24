/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sub_mini_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:39:47 by qdo               #+#    #+#             */
/*   Updated: 2024/05/24 02:49:24 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	env_underscore2(char *cmd, char **path, char ***env_o)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		if (temp == 0)
			return (0);
		temp2 = ft_strjoin(temp, cmd);
		free(temp);
		if (temp2 == 0)
			return (0);
		if (access(temp2, F_OK) == 0)
		{
			temp = ft_strjoin("_=", temp2);
			if (temp == 0)
				return (exit_code(1), free(temp), free(temp2), 0);
			i = ft_env(env_o, temp, 1);
			return (free(temp), free(temp2), i);
		}
		free(temp2);
	}
	return (-1);
}

int	env_underscore3(char ***env_o, char *cmd)
{
	char	*temp;
	int		i;

	temp = ft_strjoin("_=", cmd);
	if (temp == 0)
		return (exit_code(1), perror("ft_strjoin"), 0);
	i = ft_env(env_o, temp, 1);
	free(temp);
	return (i);
}

int	env_underscore(char **cmd, char ***env_o)
{
	int		i;
	char	**path;

	if (cmd == 0 || cmd[0] == 0)
		return (ft_env(env_o, "_=", 1));
	path = ft_path_gen(*env_o);
	if (path == 0)
		return (0);
	if (cmd[0][0] == '.' || cmd[0][0] == '/' || path[0] == 0)
	{
		free(path);
		i = 1;
		while (cmd[i])
			i++;
		return (env_underscore3(env_o, cmd[i - 1]));
	}
	i = env_underscore2(cmd[0], path, env_o);
	free_split(path);
	if (i == 0 || i == 1)
		return (i);
	return (env_underscore3(env_o, cmd[0]));
}

void	ft_sig_ter(pid_t *pid, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		kill(pid[i], SIGTERM);
}
