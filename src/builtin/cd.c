/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:00 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 15:01:44 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// TODO: invalid path
void	on_cd(t_exec e)
{
	char	*cwd;
	char	*dest_path;
	char	*home;

	if (e.argc == 1)
		return ;
	cwd = getcwd(NULL, 0);
	dest_path = e.argv[1];
	if (dest_path[0] == '~')
	{
		home = get_env_variable("HOME");
		dest_path = ft_strjoin(home, e.argv[1] + 1);
	}
	chdir(dest_path);
}
