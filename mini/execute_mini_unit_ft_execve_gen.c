/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini_unit_ft_execve_gen.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:56:25 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:35:00 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**ft_args_gen(t_mini_unit *mini_unit, char *cmd, int fd_close)
{
	char	**ret;
	int		i;

	ret = smerge(0, 0);
	if (ret == 0)
	{
		if (fd_close >= 0)
			close(fd_close);
		return (exit_code(1), NULL);
	}
	ret = smerge(ret, cmd);
	i = 0;
	while (mini_unit->cmd[++i])
	{
		ret = smerge(ret, mini_unit->cmd[i]);
		if (ret == 0)
		{
			if (fd_close >= 0)
				close(fd_close);
			return (exit_code(1), NULL);
		}
	}
	return (ret);
}

char	**ft_path_gen(char **env)
{
	char	**ret;
	int		i;

	i = -1;
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
			return (exit_code(1), perror("ft_split"), NULL);
	}
	return (ret);
}
