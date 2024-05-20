/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:25:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/20 13:37:23 by bpisak-l         ###   ########.fr       */
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
	// signal(SIGQUIT, free_exit);
	// if idle, reset prompt;
	signal(SIGINT, reset_prompt);
}

// t_exec	*simple_parse(char *line)
// {
// 	t_exec	*cmd_args;
// 	char	**argv;
// 	char	**env;

// 	env = get_env()->env_vars->env;
// 	argv = ft_split(line, " ");
// 	cmd_args = ft_calloc(1, sizeof(t_exec));
// 	cmd_args->argc = ft_arr_len(argv);
// 	cmd_args->argv = argv;
// 	cmd_args->env = env;
// 	cmd_args->cmd = argv[0];
// 	return (cmd_args);
// }

// int	process_line(char *str)
// {
// 	t_mini	*mini;
// 	char	**env;

// 	if (syntax_precheck(str) == 0)
// 		return (perror("syntax_pre wrong"), 1);
// 	env = get_env()->env_vars->env;
// 	if (env == 0)
// 		return (perror("make_env failed"), 0);
// 	mini = mini0(sndup(str, ft_strlen(str)), &env, 1);
// 	if (mini == 0)
// 		return (free_split(env), perror("mini0 call failed, syntax faied"), 1);
// 	ft_clean_programm(mini, 0, 0);
// 	ft_init_heredoc(mini);
// 	if (break_input(mini) == 0)
// 		print_err("break input sthwrong");
// 	ft_execute_mini(mini);
// 	// ft_clean_programm(0, 0, 0);
// 	return (0);
// }

// // ctrl-d exits minishell
// int	main(int argc, char const *argv[], char **env)
// {
// 	char	*line;
// 	t_exec	*cmd_args;

// 	init_signals();
// 	// what's the right exit code???
// 	if (!set_env(env))
// 		exit (1);
// 	(void)argc;
// 	(void)argv;
// 	using_history();
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (line && line[0])
// 		{
// 			cmd_args = simple_parse(line);
// 			exec_builtin(*cmd_args);
// 			add_history(line);
// 		}
// 		free(line);
// 	}
// 	return (0);
// }
