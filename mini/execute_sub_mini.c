/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sub_mini.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 03:56:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 03:22:47 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_sig_ter(pid_t *pid, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		kill(pid[i], SIGTERM);
}

//status here to check and get exit code

int	ft_wait_pid(pid_t *pid, int nbr)
{
	int	status;
	int	i;

	if (waitpid(pid[nbr - 1], &status, 0) == -1)
		return (perror("waitpid"), 1);
	i = 0;
	while (++i < nbr)
		if (wait(0) == -1)
			return (perror("wait"), 1);
	return (status);
}

pid_t	*pid_arr_create(int i)
{
	pid_t	*ret;

	ret = (pid_t *)malloc(i * sizeof(pid_t));
	if (ret == 0)
		return (perror("malloc failed"), NULL);
	return (ret);
}

int	ft_execute_sub_mini2(t_sub_mini *sub_mini)
{
	int		i;
	int		fd_in;
	int		status;
	pid_t	*pid;

	pid = pid_arr_create(sub_mini->mini_unit[0].nbr);
	if (pid == NULL)
		return (0);
	fd_in = -2;
	i = 0;
	while (++i <= sub_mini->mini_unit[0].nbr && fd_in != -1)
	{
		fd_in = ft_recursion_muni_unit_create(
				pid, &(sub_mini->mini_unit[i]), fd_in);
	}
	if (fd_in == -1)
		return (ft_sig_ter(pid, i - 1), free(pid), 0);
	close(fd_in);
	status = ft_wait_pid(pid, i - 1);
	if (WIFEXITED(status))
		return (free(pid), WEXITSTATUS(status) + 1);
	ft_sig_ter(pid, i - 1);
	free(pid);
	return (0);
}

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
				return (free(temp), free(temp2), 0);
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
		return (perror("ft_strjoin"), 0);
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
		return (env_underscore3(env_o, cmd[0]));
	}
	i = env_underscore2(cmd[0], path, env_o);
	free_split(path);
	if (i == 0 || i == 1)
		return (i);
	return (env_underscore3(env_o, cmd[0]));
}

int	ft_execute_sub_mini(t_sub_mini *sub_mini)
{
	pid_t	pid;
	int		status;

	if (sub_mini->mini_unit[0].nbr == 1)
	{
		if (dollar_underscore(sub_mini->mini_unit[1].cmd, 0, 0) == 0)
			return (0);
		if (env_underscore(sub_mini->mini_unit[1].cmd, sub_mini->env_ori) == 0)
			return (0);
		if (ft_redi_execute(&(sub_mini->mini_unit[1])) == 0)
			return (0);
		if (sub_mini->mini_unit[1].cmd == 0 && sub_mini->mini_unit[1].mini == 0)
			return (1);
		if (ft_is_builtin(&sub_mini->mini_unit[1]) == 1)
			return (ft_builtin(sub_mini->mini_unit[1].cmd, sub_mini->mini_unit[0].env_ori));
		pid = fork();
		if (pid == -1)
			return (perror("fork"), ft_clean_programm(0, EXIT_FAILURE));
		if (pid == 0)
		{
			if (sub_mini->mini_unit[1].cmd == 0 && sub_mini->mini_unit[1].mini != 0)
				return (ft_execute_mini(sub_mini->mini_unit[1].mini));
			exit(ft_execute_mini_unit(&(sub_mini->mini_unit[1]), -1, -1));
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status) + 1);
		return (0);
	}
	else
		return (ft_execute_sub_mini2(sub_mini));
}
