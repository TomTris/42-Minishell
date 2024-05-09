/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_break_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:01:50 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 22:31:00 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_break_input.h"

void	ft_free_sub_shell(t_sub_shell *sub_shell)
{
	int	i;

	i = 0;
	while (++i <= sub_shell[0].nbr)
	{
		free(sub_shell[i].str);
	}
	free(sub_shell);
}

// the str musted be allocated in the sub_shell
// and it will be freed in ft_sub_shell_create function, which
// we call at the beginning of this function.
// if first step of recursion.
// if there only 1 sub -> child process do ft_do_shell.
// else keep forking.
t_sub_shell	*ft_break_input(t_sub_shell	*sub)
{
	if (sub == 0)
	{
		sub = ft_sub_shell_create(sub[0].str);
		if (sub == 0)
			return (0);
	}
	if (sub[0].nbr == 1)
		ft_do_shell();
	else
	{
		if (ft_sub_shell_process(sub) == 0)
			return (ft_free_sub_shell(sub), 0);
	}
}
