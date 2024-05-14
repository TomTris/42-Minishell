/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:07:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 14:49:58 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// char	*make_input(int ac, char **av)
// {
// 	char	*str2;
// 	char	*str1;
// 	char	*temp;
// 	int		i;

// 	if (ac == 1)
// 		return (printf("put input\n"), NULL);
// 	str1 = ft_strdup(av[1]);
// 	if (str1 == 0)
// 		return (perror("ft_strdup"), NULL);
// 	i = 1;
// 	while (av[++i])
// 	{
// 		temp = str1;
// 		str2 = ft_strdup(av[i]);
// 		if (str2 == 0)
// 			return (free(temp), perror("ft_strdup"), NULL);
// 		str1 = ft_strjoin(str2, temp);
// 		free(temp);
// 		free(str2);
// 		if (str1 == 0)
// 			return (perror("ft_strjoin"), NULL);
// 	}
// 	return (str1);
// }

// char	**make_env(char **env)
// {
// 	char	**ret;
// 	int		i;

// 	ret = smerge(0, 0);
// 	if (ret == 0)
// 		return (0);
// 	i = -1;
// 	while (env[++i])
// 	{
// 		ret = smerge(ret, env[i]);
// 		if (ret == 0)
// 			return (0);
// 	}
// 	return (ret);
// }

t_mini	*mini0(char *str, char ***env, int lvl)
{
	t_mini	*mini;

	if (str == 0)
		return (perror("sndup"), NULL);
	mini = (t_mini *)malloc(1 * sizeof(t_mini));
	if (mini == 0)
		return (perror("Malloc failed"), free(str), NULL);
	mini->env = env;
	mini->sub_mini = 0;
	mini->str = str;
	mini->lvl = lvl;
	if (sub_mini0(mini) == 0)
	{
		free_mini(mini);
		free(mini);
		return (0);
	}
	return (mini);
}

void	mini_empty(t_mini *mini)
{
	mini->env = 0;
	mini->sub_mini = 0;
	mini->str = 0;
}

// int	main(int ac, char **av, char **env_ori)
// {
// 	t_mini	*mini;
// 	char	*str;
// 	char	**env;

// 	env = make_env(env_ori);
// 	if (env == 0)
// 		return (0);
// 	str = make_input(ac, av);
// 	if (str == 0)
// 		return (free_split(env), system("leaks mini"), 0);
// 	if (ft_isclosed(str) == 0)
// 		return (free(str), free_split(env), print_err("pre_check wrong"), system("leaks mini"), 0);
// 	mini = mini0(sndup(str, ft_strlen(str)), 0, 0);
// 	if (mini == 0)
// 		return (free(str), free_split(env), print_err("syntax wrong"), system("leaks mini"), 0);
// 	printf("\ngood input\n");
// 	free_mini(mini);
// 	free_split(env);
// 	free(mini);
// 	free(str);
// 	env = 0;
// 	mini = 0;
// 	str = 0;
// 	system("leaks mini");
// 	return (0);
// }
