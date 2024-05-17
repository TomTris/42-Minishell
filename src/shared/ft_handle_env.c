/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 04:18:57 by qdo               #+#    #+#             */
/*   Updated: 2024/05/17 18:03:28 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

static int	ft_set_shell_lvl_2(t_save *save, int i)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp = ft_itoa(ft_atoi(save->env[i] + 6) + 1);
	if (temp == 0)
		return (0);
	temp2 = sndup(save->env[i], 6);
	if (temp2 == 0)
		return (free(temp), 0);
	temp3 = ft_strjoin(temp2, temp);
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

	i = 0;
	while (env_outside[i])
		i++;
	save->env = (char **)malloc((i + 1) * sizeof(char *));
	if (save->env == 0)
		return (0);
	i = -1;
	while (env_outside[++i])
	{
		save->env[i] = ft_strdup(env_outside[i]);
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
	int		check;

	save->path_system = ft_split("/usr/local/bin:/usr/bin:/bin:\
		/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin", ":");
	if (save->path_system == 0)
		return (0);
	if (env_outside[0] == NULL)
		check = ft_env_not_exist(save);
	else
		check = ft_env_exist(save, env_outside);
	if (check == 0)
		return (free(save->path_system), 0);
	return (1);
}

//check function to check the env created which is stored in save.env
// int	main(int ac, char **av, char **env)
// {
// 	t_save save;

// 	if (av == 0)
// 		ac = 0;
// 	if (ft_save_path_system_n_env_init(&save, env) == 0)
// 		return (0);
// 	int	i;

// 	i = -1;
// 	while (save.env[++i] != 0)
// 		ft_printf("%s\n", save.env[i]);
// 	ft_printf("%d\n", i);
// 	if (ft_create_n_modify_env(&save, "PATH=abbbbfbfbf", 2) == 0)
// 		return (1);
// 	// int	i;

// 	i = -1;
// 	while (save.env[++i] != 0)
// 		ft_printf("%s\n", save.env[i]);
// 	ft_printf("%d\n", i);
// }

// this file is about: ft_save_path_system_n_env_init
//
//
// 1. Create a hidden PATH variable, which is copid from our Computer
// so that even when our programm don't have env, it will create it own env
// and it still can execute command
// 2. create it's own env. 
// when we call our programm like env -i bash, => bash doesn't get any env from
// outside but it still have some env. we need to creat it. But, there is 1
// thing. i haven't handled the PWD yet. Please, when you know how to use pwd,
// use it, and use file ft_env_changing.c with the func ft_create_n_modify_env
// to add it to the env.
//