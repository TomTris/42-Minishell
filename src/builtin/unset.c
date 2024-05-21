/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:40:30 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/21 13:45:59 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	on_unset(t_exec e)
{
	int	i;

	i = 0;
	set_exit_code(0);
	if (e.argc == 1)
	{
		ft_printf("\n");
		return ;
	}
	while (e.argv[++i])
	{
		if (is_valid_name(e.argv[i]))
			ft_create_n_modify_env(get_env(), e.argv[i], 2);
		else
		{
			set_exit_code(1);
			print_prompt();
			ft_printf("unset: `%s': not a valid identifier\n", e.argv[i]);
		}
	}
}
