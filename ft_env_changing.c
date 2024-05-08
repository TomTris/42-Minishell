/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_changing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 05:14:21 by qdo               #+#    #+#             */
/*   Updated: 2024/05/08 05:33:46 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return -1 => str1 == 0 || str2 == 0 || there is no '='
static int	ft_strcmp_til_char(char *str1, char *str2, char c)
{
	int	i;

	if (ft_find_char(str1, c) == 0 || ft_strrchr(str2, c) == NULL)
		return (-1);
	i = -1;
	while (str1[++i] != c)
		if (str1[i] != str2[i])
			return (0);
	return (1);
}

//return 1 == find + replace. Return (0) -> need to add.
static int	ft_replace_rule(t_save *save, char *str_of_add_rule)
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

static void	ft_add_rule(t_save *save, char *str_of_add_rule)
{
	int		i;
	char	**ret;

	if (ft_replace_rule(save, str_of_add_rule) == 1)
		return ;
	i = 0;
	while (save->env[i])
		i++;
	ret = (char **)malloc((i + 2) * sizeof(char *));
	if (ret == 0)
	{
		printf("something went wrong ft_add_rule in ft_env_changing.c\n");
		exit(EXIT_FAILURE);
	}
	ret[i] = ft_strdup(str_of_add_rule);
	if (ret[i] == 0)
	{
		printf("something went wrong ft_str_dup ft_add_rule in ");
		printf("ft_env_changing.c\n");
		exit(EXIT_FAILURE);
	}
	ret[i + 1] = NULL;
	i = -1;
	while (save->env[++i])
		ret[i] = save->env[i];
}

//add_replace_remove == 1 -> add / replace
//add_replace_remove == 2 -> remove
//else: Error
//if malloc failed or stuff like that, this function will clean only safe.
//need to check again
int	ft_create_n_modify_env(t_save *save, char *str_of_add_rule,
		int add_replace_remove)
{
	if (add_replace_remove == 1)
	{
		if (ft_replace_rule(save, str_of_add_rule) == 1)
			return (1);
		return (ft_add_rule(save, str_of_add_rule));
	}
	else if (add_replace_remove == 2)
		return (ft_add_rule(save, str_of_add_rule));
	else
	{
		printf("something went wrong ft_create_n_modify_env in ");
		printf("ft_env_changing.c\n");
		exit(EXIT_FAILURE);
	}
}

//need to check again
//need to check again
//need to check again