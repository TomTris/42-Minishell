/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:38:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 11:04:18 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// TODO:validate if exit arg valid int
int	is_valid_int(char *arg)
{
	(void)arg;
	return (1);
}

void	on_exit(t_exec e)
{
	if (e.argc == 1)
		exit (e.exit_code);
	if (e.argc > 2)
	{
		printf("exit: too many arguments\n");
		exit (1);
	}
	if (!is_valid_int(e.argv[1]))
	{
		printf("exit: %s: numeric argument required\n", e.argv[0]);
		exit (2);
	}
	exit (ft_atoi(e.argv[1]));
}

int	exec_builtin(t_exec exec)
{
	if (!ft_strcmp(exec.cmd, "exit"))
		on_exit(exec);
	return (0);
}