/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 11:36:36 by bpisak-l         ###   ########.fr       */
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

t_exec	*simple_parse(char *line, char **env)
{
	t_exec	*cmd_args;
	char	**exit_argv;

	exit_argv = ft_split(line, " ");
	cmd_args = ft_calloc(1, sizeof(t_exec));
	cmd_args->argc = ft_arr_len(exit_argv);
	cmd_args->argv = exit_argv;
	cmd_args->env = env;
	cmd_args->cmd = exit_argv[0];
	return (cmd_args);
}

// ctrl-d exits minishell
int	main(int argc, char const *argv[], char **env)
{
	char	*line;
	t_exec	*cmd_args;

	init_signals();
	(void)argc;
	(void)argv;
	using_history();
	while (1)
	{
		line = readline("minishell$ ");
		cmd_args = simple_parse(line, env);
		exec_builtin(*cmd_args);
		if (line[0])
			add_history(line);
		free(line);
	}
	return (0);
}
