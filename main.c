/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:31:40 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 20:38:27 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void ft_a(void)
{
	int a = 0;
	char *b = malloc(5);
	b = malloc(3);

}

void	ft_check(void)
{
	system("leaks a.out");
}

int	main(void)
{
	atexit(ft_check);
	ft_a();
	// exit(1);
	return 1;
}