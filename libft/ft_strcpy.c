/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:04:53 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 20:42:22 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = -1;
	while (src[++i])
		(dest[i]) = src[i];
	dest[i] = 0;
	return (dest);
}

void	ft_strncpy(char *dest, char *src, int i)
{
	while (--i >= 0)
		dest[i] = src[i];
	return ;
}
