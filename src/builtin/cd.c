/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:00 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 18:21:15 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_path(char *path)
{
	// char 	*oldpwd;
	struct 	stat buf;
	int		y;

	y = stat(path, &buf);
	if (y)
	{
		printf("minishell$: cd: %s: No such file or directory\n", path);
		set_exit_code(1);
		return (0);
	}
	else if (!S_ISDIR(buf.st_mode))
	{
		printf("minishell$: cd: %s: Not a directory\n", path);
		set_exit_code(1);
		return (0);
	}
	else
	{
		//TODO: set OLDPWD
		return (1);
	}
}

void	on_cd(t_exec e)
{
	char	*cwd;
	char	*dest_path;
	char	*home;
	int		res;

	if (e.argc > 2)
	{
		printf("minishell$: cd: too many arguments\n");
		set_exit_code(1);
		return ;
	}
	cwd = getcwd(NULL, 0);
	home = get_env_variable("HOME");
	if (e.argc == 1)
		dest_path = ft_strdup(home);
	else
	{
		dest_path = ft_strdup(e.argv[1]);
		if (e.argv[1][0] == '~')
		{
			free(dest_path);
			dest_path = ft_strjoin(home, e.argv[1] + 1);
		}
	}
	free(home);
	if (is_valid_path(dest_path))
		res = chdir(dest_path);
	free(dest_path);
}
