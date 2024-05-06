/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:19:34 by qdo               #+#    #+#             */
/*   Updated: 2024/05/06 05:14:43 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h> // Include readline header

void	ft_init_data(int ac, char **av, char **env, t_save *save)
{
	save->ac = ac;
	save->av = av;
	save->env = ft_split(env, save);
	if (save->env == 0)
	{
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
}
//== 1 -> export && == 2 ->unset
void	ft_creat_n_modify_env(t_save *save, char *str_of_add_rule, int add_remove)
{
	if (add_remove == 1)//add
	{//if exist -> replace, else remove
		if (ft_strcmp_til_char(str_of_add_rule,))
	}
	else if (add_remove == 2)
	{
		
	}
	else
		exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	t_save	save;

	ft_init_data(ac, av, env, &save);
}
