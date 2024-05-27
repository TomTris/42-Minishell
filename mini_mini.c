/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:07:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/28 01:33:24 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_mini	*mini0(char *str, char ***env, int lvl)
{
	t_mini	*mini;

	if (str == 0)
		return (perror("sndup"), NULL);
	mini = (t_mini *)malloc(1 * sizeof(t_mini));
	if (mini == 0)
		return (perror("Malloc failed"), exit_code(1), free(str), NULL);
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

int	main2(int ac, char **av, char ***env, char *str)
{
	t_mini	*mini;

	(void)ac;
	(void)av;
	if (syntax_precheck(str) == 0)
		return (exit_code(2), 1);
	mini = mini0(sndup(str, ft_strlen(str)), env, 1);
	if (mini == 0)
		return (1);
	ft_clean_programm(mini, 0);
	if (break_input(mini) == 0)
		return (ft_clean_programm(0, -1), 1);
	ft_execute_mini(mini);
	ft_clean_programm(0, -1);
	return (1);
}

int	ft_done(char **env)
{
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	rl_clear_history();
	dollar_underscore(0, 0, 1);
	free_split(env);
	return (exit_code(-1));
}

char	*main1(void)
{
	char	*str;
	char	*line;

	signal(SIGINT, sigint_handler1);
	if (isatty(fileno(stdin)))
		str = readline("qdo-5.2$ ");
	else
	{
		line = get_next_line(fileno(stdin));
		if (line == 0)
			return (NULL);
		str = ft_strtrim(line, "\n");
		free(line);
	}
	if (str == 0)
		return (exit_code(1), NULL);
	return (str);
}

int	main(int ac, char **av, char **env_ori)
{
	char	*str;
	char	**env;

	signal(SIGQUIT, SIG_IGN);
	env = make_env(env_ori);
	if (env == 0)
		return (exit_code(1), 0);
	if (rl_initialize() == 0)
	{
		while (1)
		{
			str = main1();
			if (str == 0)
				break ;
			signal(SIGINT, sigint_handler2);
			if (str[0] != 0)
				add_history(str);
			if (fft_isempty(str) != 1)
				main2(ac, av, &env, str);
			else
				exit_code(0);
			free(str);
		}
	}
	return (ft_done(env));
}
