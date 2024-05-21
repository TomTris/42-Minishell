/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:27:06 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/21 13:27:53 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_shared	*get_env(void )
{
	static t_shared	vars;

	return (&vars);
}

void	free_exit(int signum)
{
	t_shared	*vars;

	if (signum == SIGQUIT)
		ft_printf("exit\n");
	vars = get_env();
	exit (*vars->exit_code);
}

void	set_exit_code(int code)
{
	t_shared	*vars;

	vars = get_env();
	*vars->exit_code = code;
}

int	set_env(char **env)
{
	t_shared	*vars;
	int			res;
	char		*cwd;

	vars = get_env();
	vars->exit_code = ft_calloc(1, sizeof(int *));
	res = ft_env_init(vars, env);
	cwd = getcwd(NULL, 0);
	vars->cwd = cwd;
	set_env_variable("PWD", cwd);
	if (env[0])
		set_oldpwd(cwd);
	return (res);
}
