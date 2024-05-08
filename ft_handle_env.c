/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 04:18:57 by qdo               #+#    #+#             */
/*   Updated: 2024/05/08 05:32:16 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_set_shell_lvl_2(t_save *save, int i)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp = ft_itoa(ft_atoi(save->env[i + 6]));
	if (temp == 0)
		return (0);
	temp2 = ft_strndup(save->env[i], 6);
	if (temp2 == 0)
		return (free(temp), 0);
	temp3 = ft_strjoin(temp, temp2);
	if (temp3 == 0)
		return (free(temp), free(temp2), 0);
	free(temp);
	free(temp2);
	if (ft_create_n_modify_env(save, temp3, 1) == 0)
		return (free(temp3), 0);
	return (free(temp3), 1);
}

static int	ft_set_shell_lvl(t_save *save)
{
	int		i;

	i = -1;
	while (save->env[++i])
		if (ft_strncmp("SHLVL=", save->env[i], 6) == 0)
			break ;
	if (save->env[i] == 0)
		return (ft_create_n_modify_env(save, "SHLVL=1", 1));
	else
		return (ft_set_shell_lvl_2(save, i));
}

static int	ft_env_exist(t_save *save, char **env_outside)
{
	int	i;
	int	j;

	i = -1;
	while (env_outside[i])
		i++;
	save->env = (char **)malloc((i + 1) * sizeof(char *));
	if (save->env == 0)
		return (0);
	i = -1;
	while (env_outside[++i])
	{
		save->env[i] = ft_strdup(env_outside);
		if (save->env[i] == 0)
			break ;
	}
	if (env_outside[i] != NULL)
	{
		j = -1;
		while (++j < i)
			free(save->env[j]);
		return (free(save->env), 0);
	}
	return (ft_set_shell_lvl(save));
}

static int	ft_env_not_exist(t_save *save)
{
	char	temp[2048];

	save->env = (char **)malloc(4 * sizeof(char *));
	if (save->env == 0)
		return (0);
	if (getcwd(temp, 2048) == 0)
		return (free(save->env), 0);
	save->env[0] = ft_strdup(temp);
	if (save->env[0] == 0)
		return (free(save->env), 0);
	save->env[1] = ft_strdup("SHLVL=1");
	if (save->env[1] == 0)
		return (free(save->env[0]), free(save->env), 0);
	save->env[2] = ft_strdup("_=/usr/bin/env");
	if (save->env[2] == 0)
		return (free(save->env[0]), free(save->env[1]), free(save->env), 0);
	save->env[3] = 0;
	return (1);
}

int	ft_save_path_system_n_env_init(t_save *save, char **env_outside)
{
	int	check;

	save->path_system = ft_split("/usr/local/bin:/usr/bin:/bin:\
		/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin", ":");
	if (save->path_system == 0)
		return (0);
	if (env_outside[0] == NULL)
		check = ft_env_not_exist(save);
	else
		check = ft_env_exists(save, env_outside);
	if (check == 0)
		return (free(save->path_system), 0);
	return (1);
}