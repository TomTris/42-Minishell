/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input6_redi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:37:45 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 08:38:54 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_redirection	*mini_redi_init(t_mini_unit *mini_unit, char *str, int type_re)
{
	mini_unit->redi = (t_redirection *)malloc(2 * sizeof(t_redirection));
	if (mini_unit->redi == 0)
		return (free(str), NULL);
	mini_unit->redi[0].type_re = 1;
	mini_unit->redi[1].type_re = type_re;
	mini_unit->redi[1].str = str;
	return (mini_unit->redi);
}

int	ft_mini_redi_init2(t_mini_unit *mini_unit, t_redirection *mini_redi,
	char *ret, int type)
{
	int	i;

	i = 0;
	while (++i <= mini_unit->redi[0].type_re)
	{
		mini_redi[i].type_re = mini_unit->redi[i].type_re;
		mini_redi[i].str = mini_unit->redi[i].str;
	}
	mini_redi[i].type_re = type;
	mini_redi[i].str = ret;
	free(mini_unit->redi);
	mini_unit->redi = mini_redi;
	return (1);
}

int	ft_mini_redi_init(t_mini_unit *mini_unit, char *ret, int type)
{
	t_redirection	*mini_redi;

	if (mini_unit->redi == 0)
	{
		if (mini_redi_init(mini_unit, ret, type) == 0)
			return (free(ret), 0);
		return (1);
	}
	mini_redi = (t_redirection *)malloc
		((mini_unit->redi[0].type_re + 2) * sizeof(t_redirection));
	if (mini_redi == 0)
		return (free(ret), 0);
	mini_redi[0].type_re = mini_unit->redi[0].type_re + 1;
	return (ft_mini_redi_init2(mini_unit, mini_redi, ret, type));
}

int	ft_redi_gen(t_mini_unit *mini_unit, char *str, int *i, int type)
{
	int				cnt;
	char			*ret;

	*i += 1;
	if (type == APPEND)
		*i += 1;
	while (ft_isempty(str[*i]))
		*i += 1;
	cnt = ft_take_string(str, i);
	ret = sndup(str + *i - cnt, cnt);
	if (ret == 0)
		return (perror("sndup"), 0);
	return (ft_mini_redi_init(mini_unit, ret, type));
}
