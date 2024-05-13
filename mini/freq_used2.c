/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freq_used2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:31:37 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 06:07:28 by qdo              ###   ########.fr       */
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
	if (sign == NEWLINE)
		return (print_err("syntax error near unexpected token `new line'"));
	else
		return (print_err("sthing wrong in syn_err"));
}

//this func will free(dest), not free src, and give you a merge.
//regardless sucessful or failed
char	**smerge(char **dest, char *src)
{
	int		i;
	char	**ret;

	if (dest == 0)
	{
		dest = (char **)malloc(1 * sizeof(char *));
		if (dest == 0)
			return (perror("Malloc failed\n"), NULL);
		dest[0] = NULL;
	}
	i = 0;
	while (dest[i] != 0)
		i++;
	ret = (char **)malloc(i + 2 * sizeof(char *));
	if (ret == 0)
		return (print_err("Malloc failed\n"), NULL);
	ret[i + 1] = NULL;
	ret[i] = ft_strdup(src);
	if (ret[i] == NULL)
		return (print_err("Malloc failed\n"), NULL);
	while (--i >= 0)
		ret[i] = dest[i];
	free(dest);
	return (ret);
}

int	ft_cnt_unempty(char *str)
{
	int	i;

	i = 0;
	while (ft_isempty(str[i]) == 0 && str[i] != 0)
		i++;
	return (i);
}
