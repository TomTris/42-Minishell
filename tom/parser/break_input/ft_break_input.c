/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_break_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:01:50 by qdo               #+#    #+#             */
/*   Updated: 2024/05/10 23:49:39 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_break_input.h"

void	ft_free_sub_shell(t_sub_shell *sub_shell)
{
	int	i;

	i = 0;
	if (sub_shell != 0)
	{
		while (++i <= sub_shell[0].nbr)
		{
			free(sub_shell[i].str);
		}
		free(sub_shell);
	}
}

// the str musted be allocated in the sub_shell
// and it will be freed in ft_sub_shell_create function, which
// we call at the beginning of this function.
// if first step of recursion.
// if there only 1 sub -> child process do ft_do_shell.
// else keep forking.
t_sub_shell	*ft_break_input(t_sub_shell	*sub, char *str, char **env)
{
	int	i;

	if (sub == 0)
	{
		sub = ft_sub_shell_pre_init(str, env);
		if (sub == 0)
			return (0);
	}
	i = 0;
	while (++i <= sub[0].nbr)
	{
		ft_sub_shell_execute(sub[i]);
	}
}
//sub_shell_execute - success:1
// failed/ sth wrong - 0;