/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:57:57 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/16 16:58:24 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// A variable name must start with a character(A-Za-z) or an Underscore(_) 
// then there can be any number of characters, digits(0-9) or underscore.
int	is_valid_name(char *name)
{
	if (!name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (*name)
	{
		if (!ft_isalnum(*name) && *name!='_')
			return (0);
		name++;
	}
	return (1);
}