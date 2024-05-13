/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/10 17:40:25 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
// #include "prompt.h"

void	reset_prompt(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("^C", 1);
	rl_redisplay();
	rl_replace_line("", 1);
	rl_redisplay();
}
void	init_signals()
{
	signal(SIGQUIT, SIG_IGN);
	// if idle, reset prompt;
	signal(SIGINT, reset_prompt);
}

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;
	t_exec	exec;

	(void)argc;
	(void)argv;
	init_signals();
	using_history();
	while (1)
	{
		line = readline("minishell$ ");
		if (!ft_strncmp(line, "exit", 4))
		{
			exec = (t_exec){.cmd="exit", .argv=(char**)argv, .argc = argc, .exit_code=8, .env=env};
			exec_builtin(exec);
			printf("exit\n");
			exit (0);
		}
		if (line[0])
			add_history(line);
		free(line);
	}
	return (0);
}
