/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_break.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:07:02 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 01:13:18 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

typedef struct s_token_expect
{
	int	cmd;
	int	av;
	int	redi;
}	t_token_expect;

//print error end of line
int	print_err_eof(t_mini_unit *mini_unit)
{
	if (mini_unit->nbr < mini_unit->nbr_sum)
		return (syn_err(0, PIPE));
	if (mini_unit->sign_sub == 0)
		return (syn_err(0, NEWLINE));
	if (mini_unit->sign_sub == 1)
		return (syn_err(0, OR));
	return (syn_err(0, AND));
}

int	ft_redi(t_mini_unit *mini_unit, char *str, int *i)
{
	int	i_old;

	(*i)++;
	if (token(str + *i) == HERE_DOC || token(str + *i) == APPEND)
		(*i)++;
	while (ft_isempty(str[*i]) == 1 && str[*i])
		(*i)++;
	if (str[*i] == 0)
		return (print_err_eof(mini_unit));
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

// int	ft_syntax_break2(t_mini_unit *mini_unit,
// 		t_token_expect *tke, char *str, int *i)
// {
// 	if (token(str + *i) == C_PARENT)
// 	{
// 		if (tke->cmd == 0 && tke->av == 0 && tke->redi == 0)
// 			return (print_err("syntax error near unexpected token `)'"));
// 		return (2);
// 	}
// 	else if (token(str + *i) == O_PARENT)
// 	{
// 		if (tke->cmd != 0)
// 			return (print_err("syntax error near unexpected token `('"));
// 		if (ft_syntax_break(mini_unit, str + 1) == 0)
// 			return (0);
// 		*i += after_mlt_parent(str + *i);
// 		return (1);
// 	}
// 	tke->redi = 1;
// 	if (ft_redi(mini_unit, str, i) == 0)
// 		return (0);
// 	return (1);
// }

int	ft_syntax_break(t_mini_unit *mini_unit, char *str)
{
	int				i;
	t_token_expect	tke;

	i = 0;
	tke.cmd = 0;
	tke.av = 0;
	tke.redi = 0;
	while (str[i])
	{
		if (ft_isempty(str[i]) == 1)
			i++;
		else if (str[i] == '\'' || str[i] == '"')
		{
			tke.cmd = 1;
			i += after_quote(str + i);
		}
		else if (token(str + i) == 0 && str[i])
		{
			i++;
			tke.cmd = 1;
		}
		else if (token(str + i) == C_PARENT)
		{
			if (tke.cmd == 0 && tke.av == 0 && tke.redi == 0)
				return (print_err("syntax error near unexpected token `)'"));
			return (2);
		}
		else if (token(str + i) == O_PARENT)
		{
			if (tke.cmd != 0)
				return (print_err("syntax error near unexpected token `('"));
			if (ft_syntax_break(mini_unit, str + 1) == 0)
				return (0);
			i += after_mlt_parent(str + i);
			return (1);
		}
		else
		{
			tke.redi = 1;
			if (ft_redi(mini_unit, str, &i) == 0)
				return (0);
		}
	}
	if (tke.cmd == 0 && tke.av == 0 && tke.redi == 0)
		return (print_err_eof(mini_unit));
	return (1);
}


// void	ft_tk_zero(t_token_expect *tke, int *i)
// {
// 	*i = 0;
// 	tke->cmd = 0;
// 	tke->av = 0;
// 	tke->redi = 0;
// }


// int	ft_syntax_break(t_mini_unit *mini_unit, char *str)
// {
// 	int				i;
// 	t_token_expect	tke;

// 	ft_tk_init(&tke, i);
// 	while (str[i])
// 	{
// 		while (token(str + i) == 0)
// 			i++;
// 		if (token(str + i) == C_PARENT)
// 		{
// 			if (tke.cmd == 0 && tke.av == 0 && tke.redi == 0)
// 				return (print_err("syntax error near unexpected token `)'"));
// 			return (1);
// 		}
// 		else if (token(str + i) == O_PARENT)
// 		{
// 			if (tke.cmd != 0)
// 				return (print_err("syntax error near unexpected token `('"));
// 			tke.cmd = 1;
// 			if (ft_syntax_break(mini_unit, str + 1) == 0)
// 				return (0);
// 			i += after_mlt_parent(str + i);
// 		}
// 		else
// 		{
// 			tke.redi = 1;
// 			i = ft_redi(str, i);
// 			if (i == 0)
// 				return (0);
// 		}
// 	}
// 	if (tke.cmd == 0 && tke.av == 0 && tke.redi == 0)
// 	{
// 		if (mini_unit->sign_sub == 0)
// 			return (print_err
// 				("syntax error near unexpected token `newline'\n"));
// 		if (mini_unit->sign_sub == 1)
// 			return (print_err("syntax error near unexpected token `||'"));
// 		else
// 			return (print_err("syntax error near unexpected token `&&'"));
// 	}
// }