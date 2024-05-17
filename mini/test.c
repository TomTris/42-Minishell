/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 16:02:14 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(void)
{
	int		i;
	char	*temp;
	int		fd_pipe[2];

	pipe(fd_pipe);
	temp = get_next_line(STDIN_FILENO);
	while (temp != 0 && sncmp(temp, "LIMTTER\n", 8) != 1)
	{
		print_fd(fd_pipe[1], "%s\n", temp);
		temp = get_next_line(STDIN_FILENO);
	}
}