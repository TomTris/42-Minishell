/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:00 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 17:01:22 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// TODO: invalid path
void	on_cd(t_exec e)
{
	char	*cwd;
	char	*dest_path;
	char	*home;

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
	chdir(dest_path);
	free(dest_path);
}
