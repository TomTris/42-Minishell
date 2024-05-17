/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:10:45 by qdo               #+#    #+#             */
/*   Updated: 2024/05/15 00:11:01 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**merge_with_wildcard(char **str2, int nbr)
{
	int		i;
	int		j;
	char	**ret;
	char	**wc_expand;

	ret = smerge(0, 0);
	i = -1;
	while (str2[++i])
	{
		wc_expand = wildcard_expand(str2[i], nbr);
		if (wc_expand == 0)
			return (free_split(ret), NULL);
		j = -1;
		while (wc_expand[++j])
		{
			ret = smerge(ret, wc_expand[j]);
			if (ret == 0)
				return (free_split(wc_expand), NULL);
		}
		free_split(wc_expand);
	}
	return (ret);
}
