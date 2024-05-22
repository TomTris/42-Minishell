/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 01:29:03 by qdo               #+#    #+#             */
/*   Updated: 2024/05/21 21:02:39 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_take_string(char *str, int *i)
{
	int	cnt;

	cnt = 0;
	while (str[*i] && token(str + *i) == 0 && ft_isempty(str[*i]) != 1)
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			cnt += after_quote(str + *i);
			*i += after_quote(str + *i);
		}
		else
		{
			cnt++;
			*i += 1;
		}
	}
	return (cnt);
}

//merge s2 to s1 in append oder, both will be freed
char	**smerge2(char **s1, char **s2)
{
	int		i;
	int		j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
	{
		s1 = smerge(s1, s2[j]);
		if (s1 == NULL)
			return (free_split(s2), NULL);
		j++;
	}
	free_split(s2);
	return (s1);
}

char	**ft_cmd_create(char **cmd, char *str, char **env)
{
	char	**temp2;

// printf("***%s\n", str);
	temp2 = str_replace(str, env);
	if (temp2 == 0)
		return (free_split(cmd), NULL);
	if (temp2[0] == NULL)
		return (free(temp2), cmd);
	return (smerge2(cmd, temp2));
}

int	ft_cmd_gen(t_mini_unit *mini_unit, char *str, int *i)
{
	int		cnt;
	char	*temp;

	cnt = ft_take_string(str, i);
	temp = sndup(str + *i - cnt, cnt);
	if (temp == 0)
		return (0);
	if (mini_unit->cmd == NULL)
	{
		mini_unit->cmd = smerge(0, 0);
		if (mini_unit->cmd == 0)
			return (free(temp), 0);
	}
	mini_unit->cmd = ft_cmd_create(mini_unit->cmd, temp, *(mini_unit->env_ori));
	free(temp);
	if (mini_unit->cmd == 0)
		return (0);
	if (mini_unit->cmd[0] == 0)
		return (free(mini_unit->cmd), mini_unit->cmd = 0, 1);
	return (1);
}
