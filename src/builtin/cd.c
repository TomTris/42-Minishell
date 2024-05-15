/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:00 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/15 17:40:25 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <shared.h>

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
		return (1);
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
		if (e.argv[1][0] == '-')
		{
			dest_path = get_env_variable("OLDPWD");
			if (!dest_path[0])
			{
				printf("minishell: cd: OLDPWD not set\n");
				set_exit_code(1);
				return ;
			}
			else
				printf("%s\n", dest_path);
		}
	}
	free(home);
	if (is_valid_path(dest_path))
	{
		res = chdir(dest_path);
		cwd = getcwd(NULL, 0);
		set_cwd(cwd);
		free(cwd);
	}
	free(dest_path);
}
