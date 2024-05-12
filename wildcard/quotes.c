/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:55:20 by qdo               #+#    #+#             */
/*   Updated: 2024/05/12 00:45:04 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

//return content inside ft_siquo
char	*siquo(char *str)
{
	int		i;
	char	*ret;

	if (str[0] != '\'')
		return (ft_printf_fd(2, "ft_siquo, not '\n"), NULL);
	i = ft_strchr(str + 1, '\'') - str;
	ret = ft_strndup(str + 1, i -1);
	if (ret == 0)
		return (perror("ft_strndup"), NULL);
	return (ret);
}

char	*sdola_sign(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (str[0] != '$')
		return (fd_printf_fd(2, "ft_dl not '$'\n"), NULL);
	if ()

}
