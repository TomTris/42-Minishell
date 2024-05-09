/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:23:00 by qdo               #+#    #+#             */
/*   Updated: 2024/05/08 01:00:09 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_n(unsigned long n)
{
	if (n >= 0 && n <= 9)
		return (n + '0');
	return (n - 10 + 'a');
}

static int	ft_write_ptr1(unsigned long n, int cnt)
{
	char	a;

	if (cnt == -1)
		return (-1);
	if (n >= 16)
		cnt = ft_write_ptr1(n / 16, cnt + 1);
	if (cnt < 0)
		return (-1);
	n = n % 16;
	a = ft_n(n);
	if (write(1, &a, 1) < 0)
		return (-1);
	return (cnt);
}

int	ft_putp(unsigned long n)
{
	int	cnt;

	cnt = 2;
	if (write(1, "0x", 2) < 0)
		return (-1);
	return (ft_write_ptr1(n, cnt + 1));
}
// int	main(void)
// {
// 	int a = 234223;
// 	int *b = &a;

// 	printf("\n%d\n",ft_ptr1((unsigned long)b));
// 	printf("%p\n", b);
// }
