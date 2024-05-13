/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:06:58 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 17:02:25 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"


static int	free_split(char **to_free2)
{
	int	i;

	if (to_free2 != 0)
	{
		i = -1;
		while (to_free2[++i])
			free(to_free2[i]);
		free(to_free2);
	}
	return (0);
}

//this func will free(dest), not free src, and give you a merge.
//regardless sucessful or failed
//i = 0.
static char	**smerge(char **dest, char *src, int i)
{
	char	**ret;

	if (dest == 0)
	{
		dest = (char **)malloc(1 * sizeof(char *));
		if (dest == 0)
			return (perror("Malloc faile1d\n"), NULL);
		dest[0] = NULL;
	}
	if (src[0] == '.')
		return (dest);
	while (dest[i] != 0)
		i++;
	ret = (char **)malloc((i + 2) * sizeof(char *));
	if (ret == 0)
		return (perror("Malloc faile2d\n"), free_split(dest), NULL);
	ret[i] = ft_strdup(src);
	if (ret[i] == 0)
		return (perror("ft_strdup"), free_split(dest), free(ret), NULL);
	ret[i + 1] = NULL;
	while (--i >= 0)
		ret[i] = dest[i];
	free(dest);
	return (ret);
}

static char	**get_cwd_name(void)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**ret;

	dir = opendir(".");
	if (dir == NULL)
		return (perror("open dir"), NULL);
	while (1)
	{
		ent = readdir(dir);
		if (ent == 0)
			break ;
		ret = smerge(ret, ent->d_name, 0);
		if (ret == 0)
			return (closedir(dir), 0);
	}
	closedir(dir);
	return (ret);
}

//i = 0, j = 0
static int	ft_wc_expa_check(char *name, char *str, int i, int j)
{
	while (str[i] && name[j])
	{
		if (str[i] != '*')
		{
			if (name[j++] != str[i++])
				return (0);
		}
		else
		{
			while (str[i] == '*')
				i++;
			if (str[i] == 0)
				return (1);
			while (name[j] != 0 && name[j] != str[i])
				j++;
			if (name[j] == 0)
				return (0);
		}
	}
	while (str[i] == '*')
		i++;
	if (str[i] == 0 && name[j] == 0)
		return (1);
	return (0);
}

static char	**wc_expand2(char *str)
{
	char	**ret;

	ret = (char **)malloc(2 * sizeof(char *));
	if (ret == 0)
		return (perror("Malloc failed"), 0);
	ret[0] = ft_strdup(str);
	if (ret[0] == 0)
		return (free(ret), perror("ft_strdup"), NULL);
	ret[1] = 0;
	return (ret);
}

char	**wc_expand(char *str)
{
	char	**cwd_ns;
	int		i;
	char	**ret;

	cwd_ns = get_cwd_name();
	if (cwd_ns == 0)
		return (0);
	i = -1;
	while (cwd_ns[++i])
	{
		if (ft_wc_expa_check(cwd_ns[i], str, 0, 0) == 1)
		{
			ret = smerge(ret, cwd_ns[i], 0);
			if (ret == 0)
				return (free_split(ret), free_split(cwd_ns));
		}
	}
	free_split(cwd_ns);
	if (ret != 0)
		return (wc_expand2(str));
	return (ret);
}
