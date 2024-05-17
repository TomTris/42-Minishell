/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:38:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/17 18:03:28 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	on_exit(t_exec e)
{
	if (e.argc == 1)
		ft_printf("exit\n");
	else if (e.argc > 2)
	{
		ft_printf("exit: too many arguments\n");
		set_exit_code(1);
	}
	else if (!is_valid_int(e.argv[1]))
	{
		ft_printf("exit: %s: numeric argument required\n", e.argv[0]);
		set_exit_code(2);
	}
	else
	{
		set_exit_code(ft_atoi(e.argv[1]));
		ft_printf("exit\n");
	}
	free_exit(0);
}
