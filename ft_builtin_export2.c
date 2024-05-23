/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 05:46:35 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 06:17:07 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_is_exportpp(char **cmd, int i)
{
	int	j;

	if (ft_isdigit(cmd[i][0]) == 1 || ft_isalnum_(cmd[i][0]) != 1)
		return (0);
	j = 1;
	while (cmd[i][j] && (ft_isalnum_(cmd[i][j]) == 1 || cmd[i][j] == '+'))
	{
		if (cmd[i][j] == '+')
		{
			if (cmd[i][j + 1] == '=')
				return (1);
			return (0);
		}
		j++;
	}
	return (0);
}

int	ft_exportpp2(char ***env_o, char **cmd, int i)
{
	int		len;
	int		j;
	char	*temp;

	len = 0;
	while (cmd[i][len])
		len++;
	temp = (char *)malloc(len * sizeof(char));
	if (temp == 0)
		return (perror("malloc"), 0);
	len = 0;
	j = 0;
	while (cmd[i][len] != '+')
		temp[j++] = cmd[i][len++];
	len++;
	while (cmd[i][len])
		temp[j++] = cmd[i][len++];
	temp[j] = 0;
	i = ft_env(env_o, temp, 1);
	free(temp);
	return (i);
}

int	ft_exportpp(char ***env_o, char **cmd, int i)
{
	int		k;
	int		j;
	char	*temp;

	j = 0;
	while (cmd[i][j] != '+')
		j++;
	k = 0;
	while (env_o[0][k])
	{
		if (sncmp(env_o[0][k], cmd[i], j) == 1)
		{
			temp = ft_strjoin(env_o[0][k], cmd[i] + j + 2);
			if (temp == 0)
				return (perror("ft_strjoin"), 0);
			i = ft_env(env_o, temp, 1);
			free(temp);
			return (i);
		}
		k++;
	}
	return (ft_exportpp2(env_o, cmd, i));
}
