/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_break.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 01:52:48 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 05:40:44 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_input_break_init(t_input_break *ret, int k,
	int sign, char *str_sign)
{
	if (str_sign[0] == '&')
		sign = AND_SIGN;
	if (str_sign[1] == '|')
		sign = OR_SIGN;
	else
		sign = PIPE_SIGN;
	if (ft_strncmp(str_sign, "||", 2) == 0)
	{
		ret[k].sign_after = OR_SIGN;
		ret[++k].sign_before = OR_SIGN;
		return (2);
	}
	else if (ft_strncmp(str_sign, "|", 1) == 0)
	{
		ret[k].sign_after = PIPE_SIGN;
		ret[++k].sign_before = PIPE_SIGN;
		return (1);
	}
	else if (ft_strncmp(str_sign, "&&", 2) == 0)
	{
		ret[k].sign_after = AND_SIGN;
		ret[++k].sign_before = AND_SIGN;
		return (2);
	}
	return (-99);
}

//free str-malloced until k, without k
static void	ft_free_fail(t_input_break *ret, int k)
{
	int	i;

	i = 0;
	while (++i < k)
		free(ret[i].str);
}

static int	ft_check_parenthesis_closed(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		else if (str[i] == ')')
			return (i + 1);
		else if (str[i] == '(')
			i += ft_check_parenthesis_closed(str + i + 1);
	}
	return (0);
}

static int	ft_substr_fill(char *str, t_input_break *ret, int i, int k)
{
	k = 0;
	i = -1;
	while ((str[++i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		else if (str[i] == '(')
			i += ft_check_parenthesis_closed(str + i + 1);
		else if (ft_strncmp(str + i, "||", 2) == 0
			|| ft_strncmp(str + i, "&&", 2) == 0 || str[i] == '|')
		{
			ret[k].str = ft_strndup(str, i + 1);
			if (ret[k].str == 0)
				return (ft_free_fail(ret, k), 0);
			i = ft_input_break_init(ret, k++, 0, str + i) - 1;
			str = str + i + 1;
			i = -1;
		}
	}
	ret[k].str = ft_strdup(str);
	if (ret[k].str == 0)
		return (ft_free_fail(ret, k), 0);
	return (1);
}

t_input_break	*ft_input_break_create(char *str)
{
	t_input_break	*ret;
	int				i;
	int				size;

	size = ft_cnt_substr(str, 0, 0);
	ret = (t_input_break *)malloc((size + 1) * sizeof(t_input_break));
	if (ret == 0 || size == 0)
		return (free(ret), 0);
	i = -1;
	while (++i <= size)
	{
		ret[i].in_fd = STDIN_FILENO;
		ret[i].nbr = i;
		ret[i].out_fd = STDOUT_FILENO;
		ret[i].sign_after = 0;
		ret[i].sign_before = 0;
		ret[i].str = 0;
	}
	ret[0].nbr = size;
	if (ft_substr_fill(str, ret, 0, 0) == 0)
		return (free(ret), 0);
	return (ret);
}

