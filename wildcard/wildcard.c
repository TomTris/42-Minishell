/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:06:58 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 16:10:29 by qdo              ###   ########.fr       */
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
char	**smerge(char **dest, char *src, int i)
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

char	**get_cwd_name(void)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**ret;
	int				i;

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
			return (0);
	}
	return (ret);
}

//i = 0, j = 0
int	ft_wc_expa(char *name, char *str, int i, int j)
{
	while (str[i] && name[j])
	{
		if (str[i] != '*')
		{
			if (name[j] != str[i])
				return (0);
			i++;
			j++;
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
	if (str[i] == 0 && name[j] == 0)
		return (1);
	return (1);
}

int	main(void)
{
	char	**cwd_ns;
	int		i;
	int		j;
	char	*str = "*3c";
	char	**ret;

	i = -1;
	j = -1;
	cwd_ns = get_cwd_name();
	if (cwd_ns == 0)
		return (0);
	while (cwd_ns[++i])
	{
		if (ft_wc_expa(cwd_ns[i], str, 0, 0) == 1)
		{
			ret = smerge(ret, cwd_ns[i], 0);
			if (ret == 0)
				return (free_split(ret), free_split(cwd_ns));
		}
	}
	free_split(cwd_ns);
	if (ret == 0)
	{
		ret = (char **)malloc(2 * sizeof(char *));
		if (ret == 0)
			return (perror("Malloc failed"), 0);
		ret[0] = ft_strdup(str);
		ret[1] = 0;
	}
	i = 0;
	while (ret[i])
		printf("%s\n", ret[i++]);
	return (0);
}
