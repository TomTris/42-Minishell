/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:07:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 19:21:28 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

int	ft_lvl_cnt(int lvl_outside)
{
	static int	lvl = 0;

	if (lvl_outside > lvl)
		lvl = lvl_outside;
	return (lvl);
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
	ft_lvl_cnt(mini->lvl);
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
	// str = " << 11 << 22 << 33 << 44($23 | "" <<a) <b <d <e <f < g >hh>jj>k>ll >> mm >> nn >> pp";
	// str = "  << 44($23 | \"\" <<4) <4 <4 <4 <4 < 4>55>5>5>2/ >> 33 >> 44 >> 11";
	// str = "( 2|4 )";
	str = ">33 > 44 << 11 <<33 << 44";
	// str = "<1 <2 <3 <4";
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
		print_err("break input sthwrong");
	ft_clean_programm(0, 0, 1);
	return (0);
}
