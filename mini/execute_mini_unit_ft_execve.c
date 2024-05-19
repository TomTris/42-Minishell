/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini_unit_ft_execve.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:55:45 by qdo               #+#    #+#             */
/*   Updated: 2024/05/19 19:29:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**ft_args_gen(t_mini_unit *mini_unit, char *cmd, int fd_close)
{
	char	**ret;
	int		i;

	ret = smerge(0, 0);
	if (ret == 0)
		return (close(fd_close), NULL);
	ret = smerge(ret, cmd);
	i = 0;
	while (mini_unit->cmd[++i])
	{
		ret = smerge(ret, mini_unit->cmd[i]);
		if (ret == 0)
			return (close(fd_close), NULL);
	}
	return (ret);
}

int	ft_execve_absolut(char *cmd, char **args, char **path, char **env)
{
	int		i;
	char	*temp;
	char	*temp2;

	if (path[0] == 0)
		return (print_fd(2, " %s: No such file or directory\n", cmd));
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
			if (execve(temp2, args, env) == -1)
				return (perror("execve"), free(temp2), 1);
		}
		free(temp2);
	}
	return (print_fd(2, "%s: Command not found\n", cmd));
}

char	**ft_path_gen(char **env)
{
	char	**ret;
	int		i;

	i = 1;
	while (env[++i])
	{
		if (sncmp(env[i], "PATH=", 5) == 1)
			break ;
	}
	if (env[i] == 0)
	{
		ret = smerge(0, 0);
	}
	else
	{
		ret = ft_split(env[i] + 5, ":");
		if (ret == NULL)
			return (perror("ft_split"), NULL);
	}
	return (ret);
}

int	ft_execve(t_mini_unit *mini_unit, int fd_close)
{
	char	**path;

	if (mini_unit->cmd[0][0] == '\0')
	{
		print_fd(2, ": Command not found\n");
		if (fd_close >= 0)
			close(fd_close);
		ft_clean_programm(0, EXIT_FAILURE);
	}
	if (mini_unit->cmd[0][0] == '.' || mini_unit->cmd[0][0] == '/')
		execve(mini_unit->cmd[0], mini_unit->cmd, *(mini_unit->env_ori));
	path = ft_path_gen(*(mini_unit->env_ori));
	if (path == 0)
		ft_clean_programm(0, EXIT_FAILURE);
	ft_execve_absolut(
		mini_unit->cmd[0], mini_unit->cmd, path, *(mini_unit->env_ori));
	free_split(path);
	close(fd_close);
	ft_clean_programm(0, EXIT_FAILURE);
	return (-9);
}
