/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:47:00 by qdo               #+#    #+#             */
/*   Updated: 2024/03/10 15:11:02 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	cnt;
	char	*str_dup;

	cnt = ft_strlen((char *) s1);
	str_dup = (char *)malloc(cnt + 1);
	if (str_dup == 0)
		return (NULL);
	str_dup[cnt] = 0;
	while (cnt > 0)
	{
		cnt--;
		str_dup[cnt] = s1[cnt];
	}
	return (str_dup);
}

// int	main(void)
// {
// 	printf("%s\n",strdup(""));
// 	printf("%s\n",ft_strdup(NULL));
// 	return (0);
// }
