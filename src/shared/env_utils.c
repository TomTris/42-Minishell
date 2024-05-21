/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:43:56 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/21 13:52:58 by bpisak-l         ###   ########.fr       */
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
	res = ft_create_n_modify_env(vars, rule, 1);
	free(temp);
	free(rule);
	return (res);
}

char	*found_variable(int name_len, char *line)
{
	int		line_len;

	line_len = ft_strlen(line);
	if (line_len == name_len)
		return (NULL);
	if (line[name_len] == '=')
		return (sndup(line + name_len + 1, line_len - name_len));
	return (NULL);
}

char	*get_env_variable(char *var_name)
{
	char	**env;
	int		i;
	int		name_len;

	i = -1;
	name_len = ft_strlen((const char *)var_name);
	env = get_env()->env;
	if (!scmp(var_name, "_"))
		return (get_env()->last_arg);
	else if (!scmp(var_name, "?"))
		return (ft_itoa(get_env()->exit_code));
	while (env[++i])
	{
		if (!ft_strncmp(var_name, env[i], name_len))
			return (found_variable(name_len, env[i]));
	}
	return (NULL);
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

