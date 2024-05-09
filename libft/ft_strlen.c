/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:41:25 by qdo               #+#    #+#             */
/*   Updated: 2024/03/08 17:02:21 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *a)
{
	int		cnt;
	char	*b;

	cnt = 0;
	b = (char *)a;
	while (*b != '\0')
	{
		b++;
		cnt++;
	}
	return (cnt);
}
/*
int	main(void)
{
	char	*a;

	a = " 2 2 2 22  ";
	printf("%d",ft_strlen(a));
	printf("%lu",strlen(a));
	return (0);
}*/