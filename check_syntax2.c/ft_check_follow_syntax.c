/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_follow_syntax.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:39:22 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 06:14:14 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	token_check(char *str)
{
	if (str[0] == '|' && str[0 + 1] == '|')
		return (1);
	if (str[0] == '&' && str[0] == '&')
		return (2);
	if (str[0] == '|')
		return (3);
	if (str[0] == '(')
		return (4);
	if (str[0] == ')')
		return (5);
	return (0);
}

int	quote_len(char *str, int i)
{
	if (str[i] == '|' && str[i + 1] == '|')
		return (2);
	if (str[i] == '"' || str[i] == '\'')
		return (strrchr(str + i + 1 - str - 1, str[i]));
	return (0);
}

int	print_syn_err(char *str_ori, int size)
{
	char	*temp;

	if (size == -1)
	{
		size = 2;
		if (check_token(str_ori, 0) == 3)
			size = 1;
	}
	temp = ft_strndup(str_ori, size);
	if (temp == 0)
		perror("Malloc failed\n");
	else if (printf_fd(2, "syntax error near unexpected token `%s'") == -1)
		perror("write func in printf_fd\n");
	free(temp);
	return (0);
}

// This func checksonly after closed.
// Failed: return 0. When? after closed parenthesis,
// there should be only proper redirections or signs | || &&,
// Suucess: return the place of the closed parent.
// How to use?
// having str 012(45)
// return value: 6, sothat str[i + paren_closed_find(str + 3)] = 6
int	paren_closed_find(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = strchr(str + i + 1, str[i]) - str;
		else if (str[i] == ')')
			return (i + 1);
		else if (str[i] == '(')
			i += parenthesis_close_find(str + i + 1);
	}
	return (0);
}

int	check_after_parent(char *str, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		while (ft_isempty(str[i] != 1) && str[i])
			i++;
		if (str[i] == '<' || str[i] == '>')
		{
			j = check_n_skip_redirect(str + i, env);
			if (j == 0)
				return (0);
			i += j;
		}
		else if (str[i] == ')')
			return (i + 1);
		else
			return (0);
	}
	return (i + 1);
}

int	check_parent(char *str, char **env)
{
	int	i;
	int	check;
	int	check2;

	i = paren_closed_find(str + 1);
	check = start(str + 1);
	if (check == 0)
		return (0);
	return (check_after_parent(str + i + 1, env));
}

int	check_n_skip_redirect2(char *str, int i, char *env)
{
	char	*temp;

	temp = ft_dl_rpl(str + i + 1, env);
	if (temp == 0)
		return (perror("Malloc failed\n"), 0);
	if (temp[0] == 0)
	{
		free(temp);
		if (ft_printf_fd(2, "ambiguous redirect\n") == -1)
			perror("ft_printf_fd\n");
		return (0);
	}
	free(temp);
	i += skip_after_dl_rpl(str);
	while (ft_isempty(str[i]) != 1 && str[i])
		i++;
	return (i);
}

//
int	check_n_skip_redirect(char *str, char **env)
{
	int		i;
	int		j;

	i = 1;
	if (str[0] == str[1])
		i = 2;
	while (ft_isempty(str[i]) == 1 && str[i])
		i++;
	if (str[i] == 0)
		return (0);
	if (str[i] == '$')
	{
		j = check_n_skip_redirect2(str, i, env);
		if (j == 0)
			return (0);
		i += j;
	}
	while (ft_isalnum_(str[i]) != 0 && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = ft_strchr(str + i + 1, str[i]) - str + 1;
		if (str[i] == '(')
			return (print_syn_err(str + i, 1));
	}
	return (i);
}

int	start_check(char *str, char **env)
{
	int	i;
	int	j;
	int	check_pare;
	int	check;

	i = 0;
	check = 0;
	check_pare = 0;
	while (str[i])
	{
		if (check_pare != 0)
			check = check_pare;
		while (isempty(str[i]) == 1 && str[i])
			i++;
		if (str[i] == ')')
			return (1);
		else if (str[i] == '<' || str[i] == '>')
		{
			j = check_n_skip_redirect(str + i, env);
			if (j == 0)
				return (0);
			i += j + 1;
			check = 2;
		}
		else if (str[i] == '(')
		{
			if (check != 0)
				return (print_syn_err(str + i, 1));
			j = check_paren(str + i, env);
			if (j == 0)
				return (0);
			i += j + 1;
			check_pare = 1;
		}
		else if (str[i] == '|' || (str[i] == '&' && str[i + 1] == '&'))
		{
			if (check == 0)
				return (print_syn_err(str + i, -1));
			if (str[i] == '&' && str[i + 1] == '|')
				return (start_check(str + 2, env));
			return (start_check(str + 1, env));
		}
		if ()

	}
}

int	start_recur(char *str, char **env)
{
	int		i;
	int		check;

	i = 0;
	while (str[i])
	{
		while (isempty(str[i]) == 1 && str[i])
			i++;
		check = token_check(str + i);
		if (check == 1 || check == 2 || check == 3)
			return (print_syn_err(str + i, -1));
		else if (4 <= check && check <= 9)
		{
			if (check == 4)
				check = check_parent(str + i);
			else
				check = check_redirect(str + i);
			if (check == 0)
				return (0);
			i += check;
		}
		else
			i++;
	}
	return (1);
}
