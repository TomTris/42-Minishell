/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:27:06 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/14 14:39:49 by bpisak-l         ###   ########.fr       */
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
		printf("exit\n");
	vars = get_env();
	exit (*vars->exit_code);
}

void	set_exit_code(int code)
{
	t_shared	*vars;

	vars = get_env();
	*vars->exit_code = code;
}

void	set_cwd(char *cwd)
{
	t_shared	*vars;

	vars = get_env();
	free(vars->oldcwd);
	*vars->oldcwd = *vars->cwd;
	free(vars->cwd);
	*vars->cwd = cwd;
}

void	set_oldcwd(char *oldcwd)
{
	t_shared	*vars;

	vars = get_env();
	*vars->oldcwd = oldcwd;
}

int	set_env(char **env)
{
	t_shared	*vars;
	int			res;

	vars = get_env();
	vars->env_vars = ft_calloc(1, sizeof(t_save));
	vars->exit_code = ft_calloc(1, sizeof(int *));
	res = ft_save_path_system_n_env_init(vars->env_vars, env);
	return (res);
}

char	*get_env_variable(const char *var_name)
{
	char	**env;
	int		i;
	int		name_len;
	int		line_len;
	char	*value;

	i = -1;
	name_len = ft_strlen((const char *)var_name);
	env = get_env()->env_vars->env;
	value = ft_calloc(1, sizeof(char));
	while (env[++i])
	{
		if (!ft_strncmp(var_name, env[i], name_len))
		{
			line_len = ft_strlen(env[i]);
			if (line_len == name_len)
				return (value);
			if (env[i][name_len] == '=')
				value = ft_strndup(env[i] + name_len + 1, line_len - name_len);
		}
	}
	return (value);
}
