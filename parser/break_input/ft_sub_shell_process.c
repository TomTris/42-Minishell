/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_shell_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:43:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 22:26:19 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_break_input.h"

int	ft_set_sign_before_after(t_sub_shell *sub, char *temp, int sign)
{
	int		i;

	i = sub[0].nbr + 1;
	while (--i >= 2)
	{
		if (sub[i].str[0] == '|' && sub[i].str[1] == '|')
			sign = 1;
		else if (sub[i].str[0] == '&' && sub[i].str[1] == '&')
			sign = 2;
		else if (sub[i].str[0] =='|')
			sign = 3;
		else
			return (ft_printf_fd(2, "sth wrong in ft_sub_shell_process\n"), 0);
		temp = sub[i].str;
		if (sign == 1 || sign == 2)
			sub[i].str = ft_strdup(sub[i].str + 2);
		else
			sub[i].str = ft_strdup(sub[i].str + 1);
		if (sub[i].str == 0)
			return (free(temp), 0);
		free(temp);
		sub[i].sign_before = sign;
		sub[i - 1].sign_after = sign;
	}
	return (1);
}

int	ft_sub_shell_process(t_sub_shell *sub_shell)
{
	if (ft_set_sign_before_after(sub_shell, 0, 0) == 0)
		return (0);
	if (ft_handle_out_in_fd(sub_shell) == 0)
		return (0);
	return (1);
}
