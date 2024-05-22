/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:57:24 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 16:35:29 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_pre_set(char **cwd, char **fu_cwd, char *path)
{
	char	temp[1024];

	if (getcwd(temp, 1024) == NULL)
		return (perror("getcwd"), exit_code(1), 0);
	*cwd = ft_strjoin("OLDPWD=", temp);
	*fu_cwd = ft_strjoin("PWD=", path);
	if (*cwd == 0 || *fu_cwd == 0)
		return (exit_code(1), perror("ft_strjoin"),
			free(*fu_cwd), free(*cwd), 0);
	return (1);
}

int	ft_cd_absolut(char *path, char **cmd, char ***env)
{
	struct stat	path_stat;
	char		*cwd;
	char		*future_cwd;

	if (ft_pre_set(&cwd, &future_cwd, path) == 0)
		return (0);
	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (chdir(path) == -1)
				return (exit_code(1), perror("chdir"), 0);
			if (ft_env(env, cwd, 1) == 0 || ft_env(env, future_cwd, 1) == 0)
				return (free(cwd), free(future_cwd), 0);
			return (free(cwd), free(future_cwd), 1);
		}
		else
			return (exit_code(1),
				print_fd(2, "%s: Not a directory\n", cmd[1]), 0);
	}
	else
		return (exit_code(1),
			print_fd(2, "cd: %s: No such file or directory\n", cmd[1]), 0);
}

int	ft_cd_relativ(char **cmd, char ***env)
{
	char	temp[1024];
	char	*temp2;
	char	*temp3;
	int		ret;

	if (getcwd(temp, 1024) == NULL)
		return (exit_code(1), perror("getcwd"), 0);
	temp2 = ft_strjoin(temp, "/");
	if (temp2 != 0)
		temp3 = ft_strjoin(temp2, cmd[1]);
	if (temp2 == 0 || temp3 == 0)
		return (free(temp2), exit_code(1), perror("ft_strjoin"), 0);
	ret = ft_cd_absolut(temp3, cmd, env);
	return (free(temp2), free(temp3), ret);
}

int	ft_cd(char **cmd, char ***env)
{
	if (cmd[1] == 0 || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
		return (ft_cd_home(env));
	if (cmd[2] != 0)
		return (exit_code(1), print_err("cd: too many arguments\n"), 0);
	if (cmd[1][0] == '/')
		return (ft_cd_absolut(cmd[0], cmd, env));
	if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		return (ft_cd_oldpwd(env));
	return (ft_cd_relativ(cmd, env));
}
