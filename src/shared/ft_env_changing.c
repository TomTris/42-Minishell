/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_changing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 05:14:21 by qdo               #+#    #+#             */
/*   Updated: 2024/05/21 13:28:23 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

//return 1 == find + replace. Return (0) -> need to add.
static int	ft_replace_rule(t_shared *save, char *rule_to_add)
{
	int	i;
	int	len_to_cmp;

	len_to_cmp = 0;
	if (ft_strchr(rule_to_add, '=') != NULL)
		len_to_cmp = ft_strchr(rule_to_add, '=') - rule_to_add + 1;
	i = -1;
	while (save->env[++i] != 0 && len_to_cmp > 0)
	{
		if (ft_strncmp(save->env[i], rule_to_add, len_to_cmp) == 0)
		{
			free(save->env[i]);
			save->env[i] = ft_strdup(rule_to_add);
			if (save->env[i] == 0)
				return (perror("ft_strdup"), 0);
			return (1);
		}
	}
	return (0);
}

//add successful return 1. elsereturn 0
static int	ft_rule_add(t_shared *save, char *rule_to_add)
{
	int		i;
	int		j;
	char	**ret;

	if (ft_replace_rule(save, rule_to_add) == 1)
		return (1);
	i = 0;
	while (save->env[i])
		i++;
	ret = (char **)malloc((i + 2) * sizeof(char *));
	if (ret == 0)
		return (perror("malloc"), 0);
	ret[i + 1] = 0;
	ret[i] = save->env[i - 1];
	ret[i - 1] = ft_strdup(rule_to_add);
	if (ret[i - 1] == 0)
		return (free(ret), perror("ft_strdup"), 0);
	j = -1;
	while (++j < i - 1)
		ret[j] = save->env[j];
	free(save->env);
	save->env = ret;
	return (1);
}

static int	ft_rule_remove(t_shared *save, char *rule_to_remove)
{
	int		i;
	char	**ret;
	int		check;

	check = -1;
	i = -1;
	while (save->env[++i])
		if (ft_strncmp(save->env[i], rule_to_remove,
				ft_strlen(rule_to_remove)) == 0
			&& save->env[i][ft_strlen(rule_to_remove)] == '=')
			check = i;
	if (check == -1)
		return (1);
	ret = (char **)malloc((i) * sizeof(char *));
	if (ret == 0)
		return (0);
	free(save->env[check]);
	i = -1;
	while (++i < check)
		ret[i] = save->env[i];
	while (save->env[++i])
		ret[i - 1] = save->env[i];
	ret[i - 1] = 0;
	free(save->env);
	return (save->env = ret, 1);
}

//add_replace_remove == 1 -> add / replace
//add_replace_remove == 2 -> remove
//else: -> code wrong.
//if malloc failed or stuff like that,
//this function will clean only, what's created here and
//make save->env safe to free from a to z with function ft_free_env
int	ft_create_n_modify_env(t_shared *save, char *rule,
		int add_replace_remove)
{
	if (save == 0 || save->env == 0 || rule == 0)
		return (0);
	if (add_replace_remove == 1)
	{
		if (ft_strchr(rule, '=') == NULL)
			return (1);
		if (ft_replace_rule(save, rule) == 1)
			return (1);
		return (ft_rule_add(save, rule));
	}
	else if (add_replace_remove == 2)
	{
		if (ft_strchr(rule, '=') != NULL
			|| (rule[0] = '_' && rule[1] == '='))
			return (1);
		return (ft_rule_remove(save, rule));
	}
	else
		return (perror("ft_create_n_modify_env: wrong int check value"), 0);
}

void	ft_free_env(char **save_env)
{
	int	i;

	i = -1;
	if (save_env != 0)
		while (save_env[++i] != 0)
			free(save_env[i]);
	free(save_env);
}

//What is this file about?
// This file is a helper file that reproduces work when we want to add,
//replace or remove a env variable. Especially when people use export
// and unset
//
// how it works? cmd: "export abb=aowl"
// if there is not '=' sign in the commandline -> it doesn't work.
// if there is already a "abb" variable => the old variable will be replaced.
// unset: if we have a "abb" variable -> we unset it.
//
//How to use this file?
// 1. ft_free_env 
// to free save->env. Please do it by your own.
// all functions always free everything that it created and make things to be
// safe to be used by fr_free_env
//
//2. ft_create_n_modify_env 
// to add or replace or remove a rule.
// It takes the rule as string, for example "abb=aowl", and add/replace/remove it
// in / from env. 1 to add / replace, 2 to remove.