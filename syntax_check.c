/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:07:02 by qdo               #+#    #+#             */
/*   Updated: 2024/05/24 05:26:45 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

typedef struct s_token_expect
{
	int	cmd;
	int	paren;
	int	redi;
}	t_token_expect;

//print error end of line
static int	print_err_eof(t_mini_unit *mini_unit)
{
	if (mini_unit->nbr < mini_unit->nbr_sum)
		return (exit_code(2), syn_err(0, PIPE));
	if (mini_unit->sign_sub == 0)
	{
		if (mini_unit->lvl == 1)
			return (exit_code(2), syn_err(0, NL));
		return (exit_code(2), syn_err(")", 0));
	}
	if (mini_unit->sign_sub == 1)
		return (exit_code(2), syn_err(0, OR));
	return (exit_code(2), syn_err(0, AND));
}

static int	ft_redi(t_mini_unit *mini_unit, char *str, int *i)
{
	int	i_old;

	if (token(str + *i) == HERE_DOC || token(str + *i) == APPEND)
		(*i)++;
	(*i)++;
	while (ft_isempty(str[*i]) == 1 && str[*i])
		(*i)++;
	if (str[*i] == 0)
		return (exit_code(2), print_err_eof(mini_unit));
	if (token(str + *i) != 0)
		return (exit_code(2), syn_err(0, token(str + *i)));
	i_old = *i;
	while (ft_isempty(str[*i]) != 1 && str[*i] != 0 && token(str + *i) == 0)
	{
		*i += after_quote(str + *i);
		if (*i == i_old)
			(*i)++;
		i_old = *i;
	}
	return (1);
}

static int	syntax_check_3(t_mini_unit *mini_unit,
		t_token_expect *tke, char *str, int *i)
{
	if (token(str + *i) == O_PARENT)
	{
		if (tke->cmd != 0)
			return (exit_code(2),
				print_err("syntax error near unexpected token `('"));
		mini_unit->mini = mini0(sndup(str + *i + 1,
					after_1_parent(str + *i) - 2),
				mini_unit->env_ori, mini_unit->lvl + 1);
		if (mini_unit->mini == 0)
			return (0);
		tke->paren = 1;
		tke->cmd = 1;
		*i += after_1_parent(str + *i);
		return (1);
	}
	tke->redi = 1;
	if (ft_redi(mini_unit, str, i) == 0)
		return (0);
	return (1);
}

static int	syntax_check_2(t_mini_unit *mini_unit,
	t_token_expect *tke, char *str, int *i)
{
	if (ft_isempty(str[*i]) == 1)
	{
		(*i)++;
		return (1);
	}
	else if (str[*i] == '\'' || str[*i] == '"')
	{
		if (tke->paren == 1)
			return (exit_code(2),
				print_err("syntax error near unexpected token after `)'"));
		tke->cmd = 1;
		*i += after_quote(str + *i);
		return (1);
	}
	else if (token(str + *i) == 0 && str[*i])
	{
		if (tke->paren == 1)
			return (exit_code(2),
				print_err("syntax error near unexpected token after `)'"));
		(*i)++;
		tke->cmd = 1;
		return (1);
	}
	return (syntax_check_3(mini_unit, tke, str, i));
}

int	syntax_check(t_mini_unit *mini_unit, char *str)
{
	int				i;
	int				k;
	t_token_expect	tke;

	i = 0;
	tke.cmd = 0;
	tke.redi = 0;
	tke.paren = 0;
	while (str[i])
	{
		k = syntax_check_2(mini_unit, &tke, str, &i);
		if (k == 0)
			return (0);
		if (k == 2)
			return (1);
	}
	if (tke.cmd == 0 && tke.redi == 0 && tke.paren == 0)
	{
		exit_code(2);
		return (print_err_eof(mini_unit));
	}
	return (1);
}
