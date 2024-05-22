/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:07:47 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 04:33:15 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_replace_rule(char ***env_o, char *rule)
{
	int		i;
	int		len;
	char	*replace;

	replace = ft_strdup(rule);
	if (replace == 0)
		return (perror("ft_strdup"), 0);
	i = -1;
	len = ft_strchr(rule, '=') - rule;
	while (env_o[0][++i])
		if (sncmp(rule, env_o[0][i], len) == 1 && env_o[0][i][len] == '=')
			break ;
	free(env_o[0][i]);
	env_o[0][i] = replace;
	return (1);
}

int	ft_add_rule(char ***env_o, char *rule)
{
	int		i;
	char	*replace;
	char	**env_new;

	i = 0;
	while (env_o[0][i])
		i++;
	env_new = (char **)malloc((i + 2) * sizeof(char *));
	if (env_new == 0)
		return (0);
	replace = ft_strdup(rule);
	if (replace == 0)
		return (free(env_new), perror("ft_strdup"), 0);
	i = -1;
	while (env_o[0][++i])
		env_new[i] = env_o[0][i];
	env_new[i] = replace;
	env_new[i + 1] = 0;
	free(env_o[0]);
	*env_o = env_new;
	return (1);
}

int	ft_remove_rule(char ***env_o, char *rule)
{
	int		i;
	int		len;
	char	**env_new;

	len = ft_strlen(rule);
	i = -1;
	while (env_o[0][++i])
		if (sncmp(rule, env_o[0][i], len) == 1 && env_o[0][i][len] == '=')
			break ;
	len = 0;
	while (env_o[0][len])
		len++;
	env_new = (char **)malloc(len * sizeof(char *));
	if (env_new == 0)
		return (perror("Malloc"), 0);
	env_new[len - 1] = 0;
	free(env_o[0][i]);
	env_o[0][i] = 0;
	len = -1;
	while (env_o[0][++len])
		env_new[len] = env_o[0][len];
	while (env_o[0][len + 1] != 0)
	{
		env_new[len] = env_o[0][len + 1];
		len++;
	}
	env_new[len] = NULL;
	return (free(env_o[0]), *env_o = env_new, 1);
}

//check identifier of rule already 
int	ft_env(char ***env_o, char *rule, int unset_export)
{
	int	i;
	int	len;

	if (unset_export == 1)
	{
		i = -1;
		len = ft_strchr(rule, '=') - rule;
		while (env_o[0][++i])
			if (sncmp(rule, env_o[0][i], len) == 1 && env_o[0][i][len] == '=')
				return (ft_replace_rule(env_o, rule));
		return (ft_add_rule(env_o, rule));
	}
	else
	{
		if (rule[0] == '_' && rule[1] == '\0')
			return (1);
		i = -1;
		len = ft_strlen(rule);
		while (env_o[0][++i])
			if (sncmp(rule, env_o[0][i], len) == 1 && env_o[0][i][len] == '=')
				return (ft_remove_rule(env_o, rule));
		return (1);
	}
	return (perror("sth wrong in ft_env"), 0);
}
