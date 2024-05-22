/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:07:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 05:30:57 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// // i think this one is getting useless
// int	ft_lvl_cnt(int lvl_outside)
// {
// 	static int	lvl = 0;

// 	if (lvl_outside > lvl)
// 		lvl = lvl_outside;
// 	return (lvl);
// }

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
	// ft_lvl_cnt(mini->lvl);
	if (sub_mini0(mini) == 0)
	{
		free_mini(mini);
		free(mini);
		return (0);
	}
	return (mini);
}

int	fft_isempty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isempty(str[i]) == 1)
			i++;
		else
			break ;
	}
	if (str[i] == 0)
		return (1);
	return (0);
}

int	main2(int ac, char **av, char ***env, char *str)
// int	main(int ac, char **av, char **env_ori)
{
	t_mini	*mini;

	(void)ac;
	(void)av;
	//str = " <3 || ls && cat";
	// str = "  << 44($23 | \"\" <<4) <4 <4 <4 <4 < 4>55>5>5>2/ >> 33 >> 44 >> 11";
	// str = "( 2|4 )";
	// str = ">33 > 44 << 11 <<33 << 44";
	// char *str = "< break_input.c a";
	// char *str = "ls | grep .c | sed 's/.c/.o/'";
	// char *str = "ls -la | awk '{print $1}' | wc -l | cat -e | tr -d ' '";
	if (syntax_precheck(str) == 0)
		return (perror("syntax_pre wrong"), 1);
	mini = mini0(sndup(str, ft_strlen(str)), env, 1);
	if (mini == 0)
		return (perror("mini0 call failed, syntax faied"), 1);
	ft_clean_programm(mini, 0);
	ft_init_heredoc(mini);
	if (break_input(mini) == 0)
		print_err("break input sthwrong");
	ft_execute_mini(mini);
	ft_clean_programm(0, -1);
	return (0);
}

int	main(int ac, char **av, char **env_ori)
{
	char	*str;
	char	**env;

	env = make_env(env_ori);
	if (env == 0)
		return (perror("make_env failed"), 0);
	rl_initialize();
	while (1)
	{
		str = readline("\x1b[34mQdo&&Bori_Shell> \x1b[0m");
		if (str == 0)
			break ;
		if (fft_isempty(str) != 1)
			main2(ac, av, &env, str);
		free(str);
	}
	dollar_underscore(0, 0, 1);
	unlink(HERE_DOC_FILE);
}
