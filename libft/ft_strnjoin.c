/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 05:10:28 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 05:16:20 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *dest, char const *src, int n)
{
	int		i;
	int		j;
	char	*ret;

	ret = (char *)malloc
		(ft_strlen(((char *)dest) + n + 1) * sizeof(char));
	if (ret == 0)
		return (NULL);
	i = -1;
	while (dest[++i])
		ret[i] = dest[i];
	j++;
	while (n >= 1)
	{
		ret[i++] = src[j++];
		n--;
	}
	ret[i] = 0;
	return (ret);
}
