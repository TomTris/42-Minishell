/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 07:31:45 by qdo               #+#    #+#             */
/*   Updated: 2024/03/08 17:30:07 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 1 && *a != 0 && *b != 0)
	{
		n--;
		if (*a == *b)
		{
			a++;
			b++;
		}
		else
			return (*a - *b);
	}
	return (*a - *b);
}

// int	main(void)
// {
// 	char	*a;
// 	char	*b;

// 	a = malloc(3);
// 	b = malloc(4);
// 	a = "123";
// 	b = "1234";
// 	// *(a+3) = '\0';
// 	// *(b+3) = '\0';

// 	printf("%d\n", strncmp("","",5));
// 	printf("%d\n", ft_strncmp("","",5));

// 	return (0);
// }
