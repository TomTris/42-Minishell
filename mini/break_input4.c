/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 03:37:45 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 05:07:54 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*mini_redi_get_ret(char **temp)
{
	char	*ret;

	if (temp[0] == 0 || temp[1] != 0)
	{
		free_split(temp);
		ret = 0;
	}
	else
	{
		ret = temp[0];
		free(temp);
	}
	return (ret);
}

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

int	ft_mini_redi_init(t_mini_unit *mini_unit, char **temp, int type)
{
	char			*ret;
	t_redirection	*mini_redi;
	int				i;

	ret = mini_redi_get_ret(temp);
	if (mini_unit->redi == 0)
	{
		if (mini_redi_init(mini_unit, ret, type) == 0)
			return (free(ret), 0);
		return (1);
	}
	mini_redi = (t_redirection *)malloc
		((mini_unit->redi[0].type_re + 2)* sizeof(t_redirection));
	if (mini_redi == 0)
		return (free(ret), 0);
	mini_redi[0].type_re = mini_unit->redi[0].type_re + 1;
	i = 0;	
	while (++i <= mini_unit->redi[0].type_re)
		mini_redi[i].type_re = mini_unit->redi[i].type_re;
	mini_redi[i].type_re = type;
	mini_redi[i].str = ret;
	free_mini_unit_redi(mini_unit);
	mini_unit->redi = mini_redi;
	return (1);
}

int	ft_redi_gen(t_mini_unit *mini_unit, char *str, int *i, int type)
{
	int				cnt;
	char			*ret;
	char			**temp;

	*i += 1;
	if (type == APPEND)
		*i += 1;
	while (ft_isempty(str[*i]))
		*i += 1;
	cnt = ft_take_string(str, i);
	ret = sndup(str + *i - cnt, cnt);
	if (ret == 0)
		return (perror("sndup"), 0);
	temp = str_replace(ret, *(mini_unit->env_ori));
	free(ret);
	if (temp == 0)
		return (0);
	return (ft_mini_redi_init(mini_unit, temp, type));
}
