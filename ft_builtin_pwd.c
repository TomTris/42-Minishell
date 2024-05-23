/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 07:01:22 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:00:43 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_pwd(void)
{
	char	temp[1024];
	int		i;

	i = 0;
	while (i < 1024)
		temp[i++] = 0;
	if (getcwd(temp, 1024) == NULL)
		return (perror("getcwd"), exit_code(1), 0);
	if (printf("%s\n", temp) == -1)
		return (perror("printf"), exit_code(1), 0);
	exit_code(0);
	return (1);
}
