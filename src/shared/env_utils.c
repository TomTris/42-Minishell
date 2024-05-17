/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:43:56 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/17 18:23:28 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_env_var	*get_name_value(char *env_line)
{
	char		*eq;
	int			eq_index;
	t_env_var	*res;

	eq = ft_strchr(env_line, '=');
	res = ft_calloc(1, sizeof(t_env_var));
	if (!eq)
	{
		res->name = ft_strdup(env_line);
		res->value = ft_strdup("");
	}
	else
	{
		eq_index = eq - env_line;
		res->name = sndup(env_line, eq_index);
		res->value = sndup(eq + 1, ft_strlen(env_line) - eq_index - 1);
	}
	return (res);
}

int	set_env_variable(char *var_name, char	*var_value)
{
	t_shared	*vars;
	char		*rule;
	char		*temp;
	int			res;

	temp = ft_strjoin(var_name, "=");
	rule = ft_strjoin(temp, var_value);
	vars = get_env();
	res = ft_create_n_modify_env(vars->env_vars, rule, 1);
	free(temp);
	free(rule);
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
	value = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(var_name, env[i], name_len))
		{
			line_len = ft_strlen(env[i]);
			if (line_len == name_len)
				return (value);
			if (env[i][name_len] == '=')
				value = sndup(env[i] + name_len + 1, line_len - name_len);
		}
	}
	return (value);
}

void	set_oldpwd(char *oldcwd)
{
	t_shared	*vars;

	vars = get_env();
	set_env_variable("OLDPWD", oldcwd);
	free(vars->oldcwd);
	vars->oldcwd = ft_strdup(oldcwd);
}

void	set_cwd(char *cwd)
{
	t_shared	*vars;

	vars = get_env();
	set_oldpwd(vars->cwd);
	free(vars->cwd);
	vars->cwd = ft_strdup(cwd);
	set_env_variable("PWD", cwd);
}

