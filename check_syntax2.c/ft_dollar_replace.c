/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:22:44 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 05:35:07 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


char	*ft_dl_rpl2(char *str, char **env, int i, char *ret)
{
	char *temp;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			return (ret);
		if (str[i + 1] == '&')
			i++;
		else if (ft_isdigit(str[i + 1]) == 1)
			i = i + 2;
		else
		{
			while (ft_isalnum_(str[i]) == 1)
			{
				temp = ret;
				ret = ft_strnjoin(ret, str + i, 1);
				free(temp);
				if (ret == 0)
					return (perror("ft_strnjoin\n"), 0);
				i++;
			}
		}
	}
	return (ret);
}


//call it with index dollarsign + 1. $123 -> ft_dl_rpl(str + 1, env);
//this function will handle start from str[0] until i, with which
//ft_alnum(str[i]) != 0 && str[] != '_' && str[i] != '$'
//when $ is outside the quote.
// $1$asd => show replace of $asd
// $123$4f => return "23f"
// $123"44" => return "23"
// $123"$ds" => return "23".
char	*ft_dl_rpl(char *str, char **env)
{
	char	*ret;

	ret = ft_strdup("");
	if (ret == 0)
		return (perror("ft_strndup ft_dl_rpl\n"), 0);
	return (ft_dl_rpl2(str, env, 0, ret));
}

//plus this func -> to the new char, not a part of $_replace
int	skip_after_dl_rpl(char *str, int i)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '&')
				i++;
			else if (ft_isdigit(str[i + 1]) == 1)
				i = i + 2;
			else
			{
				while (ft_isalnum_(str[i]) == 1)
					i++;
			}
		}
		else
			return (i + 1);
	}
	return (1);
}
