/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/18 03:18:50 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	main(int ac, char **av, char **env)
{
ac = 0;
av = 0;
env = 0;

	int	i;
	int	j;
	int	k;

	i = open("ft_other1.c", O_RDONLY);
	j = open("ft_other2.c", O_RDONLY);
	k = open("ft_other3.c", O_RDONLY);
	close(i);
	close(j);
	close(k);
	i = open("ft_other1.c", O_RDONLY);
	return (0);
}
