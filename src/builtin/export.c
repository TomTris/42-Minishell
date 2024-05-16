/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:03:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/16 12:03:11 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// A variable name must start with a character(A-Za-z) or an Underscore(_) 
// then there can be any number of characters, digits(0-9) or underscore.
int	is_valid_name(char *name)
{
	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name!='_')
			return (0);
		name++;
	}
	return (1);

}

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
		res->name = ft_strndup(env_line, eq_index);
		res->value = ft_strndup(eq + 1, ft_strlen(env_line) - eq_index - 1);
	}
	return (res);
}

int	export_arg(char *arg)
{
	t_env_var	*env_var;

	env_var = get_name_value(arg);
	if (!is_valid_name(env_var->name))
		return (0);
	set_env_variable(env_var->name, env_var->value);
	return (1);
}


void	print_all_exported(void)
{
	char	**env;
	int		i;
	t_env_var	*env_var;

	env = get_env()->env_vars->env;
	i = -1;
	while (env[++i])
	{
		env_var = get_name_value(env[i]);
		printf("declare -x %s=\"%s\"\n", env_var->name, env_var->value);
	}
}

// If no names are supplied, a list of names of 
// all exported variables is displayed. 
// The return status is zero unless --- one of 
// the names is not a valid shell variable name
void	on_export(t_exec e)
{
	int		i;
	int		all_correct;

	(void)e;
	if (e.argc == 1)
		print_all_exported();
	all_correct = 1;
	i = 0;
	while (++i < e.argc)
	{
		if (!export_arg(e.argv[i]))
		{
			printf("export: `%s': not a valid identifier\n", e.argv[i]);
			all_correct = 0;
		}
	}
	if (!all_correct)
		set_exit_code(1);
	else
		set_exit_code(0);
}
