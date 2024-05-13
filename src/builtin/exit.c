/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:38:07 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/13 11:42:01 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	printf("exit\n");
	exit (ft_atoi(e.argv[1]));
}
