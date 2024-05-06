/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_changing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 05:14:21 by qdo               #+#    #+#             */
/*   Updated: 2024/05/06 05:22:21 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_char(char *str, char c)
{
	int	i;

	i = 0;
	if (str == 0)
		return (-1);
	while (str[i])
		if (str[i] == c)
			return (1);
	return (0);
}

//return -1 => str1 == 0 || str2 == 0 || there is no '='
int	ft_strcmp_til_char(char *str1, char *str2, char c)
{
	int	i;

	if (ft_find_char(str1, c) == 0 || ft_find_char(str2, c) == 0)
		return (-1);
	i = -1;
	while (str1[++i] != c)
		if (str1[i] != str2[i])
			return (0);
	return (1);
}

//return 1 == find + replace. Return (0) -> need to add.
int	ft_replace_rule(t_save *save, char *str_of_add_rule)
{
	int	i;

	i = -1;
	while (save->env[i++] != 0)
	{
		if (ft_strcmp_til_char(save->env[i], str_of_add_rule, '=') == 1)
		{
			free(save->env[i]);
			save->env[i] = ft_strdup(str_of_add_rule);
			if (save->env[i] == 0)
			{
				printf("ft_add_rule malloc\n");
				exit(EXIT_SUCCESS);
			}
			return (1);
		}
	}
	return (0);
}


void	ft_add_rule(t_save *save, char *str_of_add_rule)
{
	int	i;

	if (ft_replace_rule(save, str_of_add_rule) == 1)
		return ;
	i = 0;
	while (save->env[i])
		i++;
	

}

void	ft_creat_n_modify_env(t_save *save, char *str_of_add_rule, int add_remove)
{
	if (add_remove == 1)//add
	{//if exist -> replace, else remove
		if (ft_strcmp_til_char(str_of_add_rule,))
	}
	else if (add_remove == 2)
	{
		
	}
	else
		exit(EXIT_FAILURE);
}