/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dl_rpl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:31:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 23:35:25 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char *ft_dl_rpl_lvl0(char *str, int *i_ori, char **env)
{
	char	*ret;
	int		i;
	int		j;
	int		k;

	i = *i_ori;
	if (ft_isdigit(str[i]) == 1)
	{
		ret = ft_strdup("");
		if (ret == 0)
			return (perror("ft_strdup"), NULL);
		return (ret);
	}
	ret = ft_strndup(str + i + 1, ft_dl_skip_lv0(str, i) - i - 1);
	if (ret == 0)
		return (perror("ft_strdup"), NULL);
	j = 0;
	k = ft_strlen(ret);
	while (env[j])
	{
		if (ft_strncmp(ret, env[j], k) == 0 && env[j][k] == '=')
		{
			free(ret);
			ret = ft_strdup(env[j] + k + 1);
			if (ret == 0)
				return (perror("ft_strdup"), NULL);
			return (ret);
		}
		j++;
	}
	return (ret);
}

char	*ft_dl_rpl_lvl1_1(char *str, int *i_ori, char **env)
{
	int		i;
	char	*ret;
	char	*temp;
	char	*temp2;

	i = *i_ori + 1;
	ret = ft_strdup("");
	if (ret == 0)
		return (0);
	while (str[i] != '"')
	{
		if (str[i] == '\'')
			i = ft_strchr(str + i + i, '\'') - str + 1;
		else if (str[i] == '$')
		{
			temp = ft_dl_rpl_lvl0(str, &i, env);
			temp2 = ret;
			ret = ft_strjoin(ret, temp);
			free(ret);
			free(temp);
			if 
		}
	}
}

char	*ft_dl_rpl_lvl1(char *str, int *i_ori, char **env)
{
	char	*ret;
	char	*temp;
	char	*temp2;
	int		i;

	i = *i_ori;
	ret = ft_dl_rpl_lvl0(str, i_ori, env);
	if (ret == 0)
		return (0);
	i = ft_dl_skip_lv0(str, i);
	while (str[i] && ft_isalnum_(str[i]) == 1 && (str[i] == '"' || str[i] == '\''))
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			temp = ft_dl_rpl_lvl1_1(str, i, env);
			if (temp == 0)
				return (free(ret), 0);
			temp2 = ret;
			ret = ft_strjoin(ret, temp);
			free(temp);
			free(ret);
			if (ret == 0)
				return (perror("ft_strjoin"), NULL);
			i = ft_strchr(str + i + 1, str[i]) - str + 1;
		}
	}
	*i_ori = i;
	return (ret);
}

//call it with index dollarsign + 1. $123 -> ft_dl_rpl(str + 1, env);
//this function will handle start from str[0] until i, with which
//ft_alnum(str[i]) != 0 && str[] != '_' && str[i] != '$'
//when $ is outside the quote.
// $1$asd => show replace of $asd
// $123$4f => return "23f"
// $123"44" => return "23"
// $123"$ds" => return "23".
char	*ft_dl_rpl_lvl2(char *str, int i, char **env)
{
	char	*ret;
	char	*temp;
	char	*temp2;
	int		j;

	ret = ft_strdup("");
	if (ret == 0)
		return (perror("ft_strdup\n"), NULL);
	while (str[i] == '$')
	{
		temp = ft_dl_rpl_lvl1(str, &i, env);
		if (temp == 0)
			return (free(ret), NULL);
		temp2 = ret;
		ret = ft_strjoin(temp2, temp);
		free(temp);
		free(temp2);
		if (ret == 0)
			return (perror("ft_strjoin"), NULL);
	}
	return (ret);
}



//skip only what belongs to $
// $$$$$$ -> return 1;
// $2abc$mk => abc$mk left
// $3hn -> hn left
// $gffbd4"ggr"sf -> "ggr"sf left
int	ft_dl_skip_lv0(char *str, int i)
{
	if (str[i] != '$')
		return (perror("non $\n"), 0);
	while (str[i] == '$')
		i++;
	if (ft_isdigit(str[i]) == 1)
	{
		i++;
		return (i);
	}
	while (ft_isalnum_(str[0]) && str[i])
		i++;
	return (i);
}

// skip what belongs to $ and the whole str until, but ignore ""
// $ ||  (empty or 0 or tokens)
// $$$2abc$5bltg => $5bltg left
// $3hn$d -> $d left
// $3hndqw"l$c3324"$vrm -> $vrm left
int	ft_dl_skip_lvl1(char *str, int i)
{
	if (str[i] != '$')
		return (perror("non $\n"), 0);
	while (str[i] == '$')
		i++;
	while (ft_isempty(str[i]) != 1 && str[i] != 0 &&
		token_check(str + i) == 0 && str[i] != '$')
	{
		if (str[i] == '"' || str[i] == "'")
			i = ft_skip_quote(str, i);
		else
			i++;
	}
	return (i);
}

//skip until (empty or 0 or tokens)
// $m95hbG4532$ -> nothing left.
int	ft_dl_skip_lvl2(char *str, int i)
{
	if (str[i] != '$')
		return (0);
	while (ft_isempty(str[i]) != 0 && str[i] && token_check(str + i) == 0)
	{
		if (str[i] == '"' || str[i] == '\'')
			i = ft_strchr(str + i + 1, str[i]) - str + 1;
		else if (str[i] == '$')
			i = ft_dl_skip_lvl1(str, i);
		else
			i++;
	}
	return (i);
}

int	main(int ac, char **argv, char **env)
{
	char *str = "$a555$4";

	if (argv != 0)
		ac = 0;
	printf("%s\n", ft_dl_rpl_lvl2(str, 0, env));
	printf("22\n");
	return (0);
}
