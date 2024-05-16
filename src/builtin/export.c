/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:03:11 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/16 16:58:17 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export_arg(char *arg)
{
	t_env_var	*v;

	v = get_name_value(arg);
	if (!is_valid_name(v->name))
		return (0);
	set_env_variable(v->name, v->value);
	free(v->name);
	free(v->value);
	free(v);
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
			print_prompt();
			printf("export: `%s': not a valid identifier\n", e.argv[i]);
			all_correct = 0;
		}
	}
	if (!all_correct)
		set_exit_code(1);
	else
		set_exit_code(0);
}
