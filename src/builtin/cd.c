/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:05:00 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 13:00:46 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	on_cd(t_exec e)
{
	char	*cwd;
	int		i;

	if (e.argc == 1)
		return ;
	cwd = getcwd(NULL, 0);
	chdir(e.argv[1]);
	i = -1;
	// if (!ft_strcmp(e.argv[1], "~"))
	// 	dest = HOME
	while (e.env[++i])
		printf("%s\n", e.env[i]);
}
