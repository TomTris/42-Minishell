/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:07:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 05:37:42 by qdo              ###   ########.fr       */
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

static char	**make_env(char **env)
{
	char	**ret;
	int		i;

	ret = smerge(0, 0);
	if (ret == 0)
		return (0);
	i = -1;
	while (env[++i])
	{
		ret = smerge(ret, env[i]);
		if (ret == 0)
			return (0);
	}
	return (ret);
}

t_mini	*mini0(char *str, char ***env, int lvl)
{
	t_mini	*mini;

	if (str == 0)
		return (perror("s1ndup"), NULL);
	mini = (t_mini *)malloc(1 * sizeof(t_mini));
	if (mini == 0)
		return (perror("Malloc failed"), free(str), NULL);
	mini->env = env;
	mini->sub_mini = 0;
	mini->str = str;
	mini->lvl = lvl;
	mini->fd_heredoc = -1;
	if (sub_mini0(mini) == 0)
	{
		free_mini(mini);
		free(mini);
		return (0);
	}
	return (mini);
}

int	main(int ac, char **av, char **env_ori)
{
	t_mini	*mini;
	char	*str;
	char	**env;

	(void)ac;
	(void)av;
	str = " << 33 << 33 << 44 << 44($23 | "" <<4) <4 <4 <4 <4 < 4>55>5>5>2/ >> 33 >> 44 >> 11";
	// str = "  << 44($23 | \"\" <<4) <4 <4 <4 <4 < 4>55>5>5>2/ >> 33 >> 44 >> 11";
	// str = "( 2|4 )";
	if (syntax_precheck(str) == 0)
		return (perror("syntax_pre wrong"), 1);
	env = make_env(env_ori);
	if (env == 0)
		return (perror("make_env failed"), 0);
	mini = mini0(sndup(str, ft_strlen(str)), &env, 1);
	if (mini == 0)
		return (free_split(env), perror("mini0 call failed, syntax faied"), 1);
	ft_clean_programm(mini, 0, 0);
	ft_init_heredoc(mini);
	if (break_input(mini) == 0)
		print_err("break input sthwrong\n");
	ft_clean_programm(0, 0, 0);
	return (0);
}
