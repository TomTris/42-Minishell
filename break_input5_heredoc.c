/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input5_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:23:32 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 19:26:47 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_512(char *temp)
{
	if (print_fd(2, "Can't store more than 512 bytes, force") == -1
		|| print_fd (2, " break and keep doing execution!\n") == -1)
		return (exit_code(1), perror("printf_fd"), free(temp), 0);
	return (free(temp), 1);
}
