/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 05:24:52 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:48:05 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	token(char *str)
{
	if (str[0] == '|' && str[0 + 1] == '|')
		return (OR);
	if (str[0] == '&' && str[0 + 1] == '&')
		return (AND);
	if (str[0] == '|')
		return (PIPE);
	if (str[0] == '(')
		return (O_PARENT);
	if (str[0] == ')')
		return (C_PARENT);
	if (str[0] == '<' && str[1] == '<')
		return (HERE_DOC);
	if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	if (str[0] == '<')
		return (RE_IN);
	if (str[0] == '>')
		return (RE_OUT);
	return (0);
}

int	after_quote(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '"' && str[0] != '\'')
		return (0);
	while (str[i] == '"' || str[i] == '\'')
		i += ft_strchr(str + i + 1, str[i]) - (str + i) + 1;
	return (i);
}

int	after_mlt_parent(char *str)
{
	if (str[0] == 0 || str[0] != '(')
		return (0);
	return (after_1_parent(str)
		+ after_mlt_parent(str + after_1_parent(str) + 1));
}

int	after_1_parent(char *str)
{
	int	i;
	int	cnt;

	cnt = 0;
	if (str[0] != '(')
		return (0);
	i = -1;
	while (str[++i])
	{
		i += after_quote(str + i);
		if (str[i] == '(')
			cnt++;
		if (str[i] == ')')
			cnt--;
		if (cnt == 0)
			return (i + 1);
	}
	print_err("sth wrong in ater_1_parent");
	return (0);
}

int	print_err(char *str)
{
	if (print_fd(2, "%s\n", str) == -1)
	{
		exit_code(1);
		perror("print_fd");
	}
	return (0);
}
