/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_wildcard1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:48:55 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:44:45 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	ft_sort_ascii(char **ret)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (ret[i])
		i++;
	while (i-- > 1)
	{
		j = 0;
		while ((j + 1) <= i - 1)
		{
			if (ft_strncmp(ret[j], ret[j + 1], ft_strlen(ret[i]) + 1) > 0)
			{
				temp = ret[j];
				ret[j] = ret[j + 1];
				ret[j + 1] = temp;
			}
			j++;
		}
	}
}

static char	**get_cwd_name(void)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**ret;

	dir = opendir(".");
	if (dir == NULL)
		return (exit_code(1), perror("open dir"), NULL);
	ret = smerge(0, "");
	if (ret == 0)
		return (exit_code(1), closedir(dir), NULL);
	while (1)
	{
		ent = readdir(dir);
		if (ent == 0)
			break ;
		if (ent->d_name[0] != '.')
		{
			ret = smerge(ret, ent->d_name);
			if (ret == 0)
				return (closedir(dir), NULL);
		}
	}
	closedir(dir);
	ft_sort_ascii(ret);
	return (ret);
}

//j = 0, nbr
static int	ft_wc_expa_check(char *name, char *str, int j, int nbr)
{
	int	i;

	i = 0;
	while (str[i] && name[j])
	{
		if (str[i] == nbr)
		{
			while (str[i] == nbr)
				i++;
			if (str[i] == 0)
				return (1);
			while (name[j] != 0 && name[j] != str[i])
				j++;
			if (name[j] == 0)
				return (0);
		}
		else
			if (name[j++] != str[i++])
				return (0);
	}
	while (str[i] == nbr)
		i++;
	if (str[i] == 0 && name[j] == 0)
		return (1);
	return (0);
}

static void	ft_recovery(char **ret, int nbr)
{
	int	i;

	if (ret == 0 || ret[0] == 0)
		return ;
	i = -1;
	while (ret[0][++i])
		if (ret[0][i] == nbr)
			ret[0][i] = '*';
}

//if str[0] = 0 -> return str
char	**wildcard_expand(char *str, int nbr)
{
	char	**cwd_ns;
	int		i;
	char	**ret;

	cwd_ns = get_cwd_name();
	if (cwd_ns == 0)
		return (0);
	ret = smerge(0, 0);
	if (ret == 0)
		return (exit_code(1), free_split(cwd_ns), NULL);
	i = -1;
	while (cwd_ns[++i])
	{
		if (ft_wc_expa_check(cwd_ns[i], str, 0, nbr) == 1)
		{
			ret = smerge(ret, cwd_ns[i]);
			if (ret == 0)
				return (exit_code(1), free_split(ret), free_split(cwd_ns), NULL);
		}
	}
	free_split(cwd_ns);
	if (ret[0] == 0)
		ret = smerge(ret, str);
	ft_recovery(ret, nbr);
	return (ret);
}
