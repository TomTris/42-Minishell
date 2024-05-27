/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_cd_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:35:09 by qdo               #+#    #+#             */
/*   Updated: 2024/05/27 21:09:35 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_cd_home(char	***env)
{
	char	*temp2;
	char	**temp;
	int		ret;
	int		i;

	i = -1;
	while (env[0][++i])
		if (sncmp("HOME=", env[0][i], 5) == 1)
			break ;
	if (env[0][i] == 0 || sncmp("HOME=", env[0][i], 5) != 1)
		return (print_fd(2, "cd: HOME not set\n"), exit_code(1), 0);
	temp2 = ft_strdup(env[0][i] + 5);
	if (temp2 == 0)
		return (exit_code(1), perror("ft_strdup"), 0);
	temp = smerge(0, 0);
	if (temp != 0)
		temp = smerge(temp, temp2);
	if (temp != 0)
		temp = smerge(temp, temp2);
	if (temp == 0)
		return (exit_code(1), free(temp2), 0);
	ret = ft_cd_absolut(temp2, temp, env);
	free_split(temp);
	free(temp2);
	return (ret);
}

int	ft_cd_oldpwd(char ***env)
{
	char	*temp2;
	char	**temp;
	int		ret;
	int		i;

	i = -1;
	while (env[0][++i])
		if (sncmp("OLDPWD=", env[0][i], 7) == 1)
			break ;
	if (env[0][i] == 0 || sncmp("OLDPWD=", env[0][i], 7) != 1)
		return (print_fd(2, "cd: OLDPWD not set\n"), exit_code(1), 0);
	temp2 = ft_strdup(env[0][i] + 7);
	if (temp2 == 0)
		return (exit_code(1), perror("ft_strdup"), 0);
	temp = smerge(0, 0);
	if (temp != 0)
		temp = smerge(temp, temp2);
	if (temp != 0)
		temp = smerge(temp, temp2);
	if (temp == 0)
		return (exit_code(1), free(temp2), 0);
	ret = ft_cd_absolut(temp2, temp, env);
	free_split(temp);
	free(temp2);
	return (ret);
}
