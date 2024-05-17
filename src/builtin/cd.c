/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:00 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/17 18:30:13 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <shared.h>

int	is_valid_path(char *path)
{
	struct stat	buf;
	int			y;

	y = stat(path, &buf);
	if (y)
	{
		print_prompt();
		ft_printf("cd: %s: No such file or directory\n", path);
		set_exit_code(1);
		return (0);
	}
	else if (!S_ISDIR(buf.st_mode))
	{
		print_prompt();
		ft_printf("cd: %s: Not a directory\n", path);
		set_exit_code(1);
		return (0);
	}
	else
		return (1);
}

void	navigate_to_path(char *path)
{
	int		res;
	char	*cwd;

	res = chdir(path);
	cwd = getcwd(NULL, 0);
	set_cwd(cwd);
	free(cwd);
	set_exit_code(0);
}

void	navigate_to_oldpwd()
{
	char	*dest_path;

	dest_path = get_env_variable("OLDPWD");
	if (!dest_path[0])
	{
		print_prompt();
		ft_printf("cd: OLDPWD not set\n");
		set_exit_code(1);
		return ;
	}
	else
		ft_printf("%s\n", dest_path);
	free (dest_path);
}

void	navigate(char *dest_path)
{
	if (is_valid_path(dest_path))
		navigate_to_path(dest_path);
	free(dest_path);
}

void	navigate_relative_home(char *path, char *home)
{
	char	*dest_path;

	dest_path = ft_strdup(home);
	if (ft_strlen(path) > 1)
	{
		free(dest_path);
		dest_path = ft_strjoin(home, path + 1);
	}
	navigate(dest_path);
}

void	on_cd(t_exec e)
{
	char	*dest_path;
	char	*home;

	if (e.argc > 2)
	{
		print_prompt();
		ft_printf("cd: too many arguments\n");
		set_exit_code(1);
		return ;
	}
	home = get_env_variable("HOME");
	dest_path = NULL;
	if (e.argc == 1)
		dest_path = ft_strdup(home);
	else if (e.argv[1][0] == '~')
		navigate_relative_home(e.argv[1], home);
	else if (e.argv[1][0] == '-' && ft_strlen(e.argv[1]) == 1)
		return (navigate_to_oldpwd());
	else
	{
		dest_path = ft_strdup(e.argv[1]);
		navigate(dest_path);
	}
	free(home);
}
