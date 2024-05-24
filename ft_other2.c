/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:31:37 by qdo               #+#    #+#             */
/*   Updated: 2024/05/24 05:27:27 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//str != 0 -> print str.  token `%s' %s will be replaced
//if (str == 0) -> print based on sign
//if sign not proper -> perror - sthwrong.
int	syn_err(char *str, int sign)
{
	if (str != 0)
	{
		if (print_fd(2, "syntax error near unexpected token `%s'\n", str) == -1)
			perror("printf_fd");
		return (0);
	}
	if (sign == OR)
		return (print_err("syntax error near unexpected token `||'"));
	if (sign == AND)
		return (print_err("syntax error near unexpected token `&&'"));
	if (sign == PIPE)
		return (print_err("syntax error near unexpected token `|'"));
	if (sign == RE_IN)
		return (print_err("syntax error near unexpected token `<'"));
	if (sign == RE_OUT)
		return (print_err("syntax error near unexpected token `>'"));
	if (sign == APPEND)
		return (print_err("syntax error near unexpected token `>>'"));
	if (sign == HERE_DOC)
		return (print_err("syntax error near unexpected token `<<'"));
	if (sign == NL)
		return (print_err("syntax error near unexpected token `new line'"));
	if (sign == O_PARENT)
		return (print_err("syntax error near unexpected token `('"));
	return (print_err("sthing wrong in syn_err"));
}

//this func will free(dest), not free src, and give you a merge.
//regardless sucessful or failed
//i = 0
//dest ==0 -> create 2dimen arr.
char	**smerge(char **dest, char *src)
{
	char	**ret;
	int		i;

	if (dest == 0)
	{
		dest = (char **)malloc(1 * sizeof(char *));
		if (dest == 0)
			return (perror("Malloc faile1d\n"), NULL);
		dest[0] = NULL;
		return (dest);
	}
	i = 0;
	while (dest[i] != 0)
		i++;
	ret = (char **)malloc((i + 2) * sizeof(char *));
	if (ret == 0)
		return (perror("Malloc faile2d\n"), free_split(dest), NULL);
	ret[i] = ft_strdup(src);
	if (ret[i] == 0)
		return (perror("ft_strdup"), free_split(dest), free(ret), NULL);
	ret[i + 1] = NULL;
	while (--i >= 0)
		ret[i] = dest[i];
	free(dest);
	return (ret);
}
