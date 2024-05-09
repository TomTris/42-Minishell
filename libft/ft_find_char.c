/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:35:14 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 03:38:58 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.a"

// works as ft_strchr, but it takes a string to_find as argument
int	ft_char_find(char *str, char *to_find1, char *to_find2, char *to_find3)
{
	if (to_find == 0)
		return (0);
	if ((char)c == '\0')
	{
		while (*s != 0)
			s++;
		return ((char *)s);
	}
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
