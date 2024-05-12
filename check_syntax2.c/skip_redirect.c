/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:25:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 22:32:03 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	token_check(char *str)
{
	if (str[0] == '|' && str[0 + 1] == '|')
		return (1);
	if (str[0] == '&' && str[0 + 1] == '&')
		return (2);
	if (str[0] == '|')
		return (3);
	if (str[0] == '(')
		return (4);
	if (str[0] == ')')
		return (5);
	if (str[0] == '<')
		return (6);
	if (str[0] == '>')
		return (7);
	return (0);
}

char	*ft_dl_rpl_lvl1(char *str, int i, char **env)
{
	char	*ret;
	int		j;

	while (str[i] == '$')
		i++;
	if (ft_isdigit(str[i]) == 1)
	{
		ret = ft_strdup("");
		if (ret == 0)
			return (perror("ft_strdup"), NULL);
		return (ret);
	}
	j = 1;
	while (ft_isalnum_(str[i + j]) != 1)
		j++;
	ret = ft_strndup(str + i, j);
	if (ret == 0)
		return (perror("ft_strdup"), NULL);
	i = -1;
	while (env[++i])
	{
		j = ft_strlen(ret);
		if (ft_strncmp(ret, env[i], j) == 0 && env[i][j] == '=')
		{
			free(ret);
			ret = ft_strdup(env[i] + j + 1);
			if (ret == 0)
				return (perror("ft_strdup"), NULL);
			return (ret);
		}
	}
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
		temp = ft_dl_rpl_lvl1(str, i, env);
		if (temp == 0)
			return (free(ret), NULL);
		temp2 = ret;
		ret = ft_strjoin(temp2, temp);
		free(temp);
		free(temp2);
		if (ret == 0)
			return (perror("ft_strjoin"), NULL);
		while ()
	}
	return (ret);
}


int	ft_check_$_alone(char *str, int i)
{
	if (str[i] != '$')
		return (-1);
	if (str[i] == '$' && ft_isempty(str[i + 1]) == 1)
		return (1);
	return (0);
}
//skip only what belongs to $
// $$$2abc$mk => abc$mk left
// $3hn -> hn left
// $gffbd4"ggr"sf -> "ggr"sf left
int	ft_dl_skip_lv0(char *str, int i)
{
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

//skip what belongs to $ and the whole str until we get the next $
// $$$2abc$5bltg => $5bltg left
// $3hn$d -> $d left
// $3hndqw"3324"$vrm -> $vrm left
int	ft_dl_skip_lvl1(char *str, int i)
{
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

//skip what belongs to $ and the whole str even we get another $
// $m95hbG4532$ -> nothing left.
int	ft_dl_skip_lvl2(char *str, int i)
{
	if (str[i] != '$')
		return (i);
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

int	skip_redirect(char *str, int i, char **env)
{
	char	*check;
return (0);
	check = ft_dl_rpl_lvl2(str, i, env);
	if (check == 0 || check[0] == 0)
		return (free(check), 0);
	if (check[0] == 0)
	{
		free(check);
		if (ft_printf_fd(2, "ambigious redirect\n") == -1)
			perror("ft_printf_fd");
		return (0);
	}
	free(check);
	return (ft_dl_skip_lvl2(str, i));
}

int	main(int ac, char **argv, char **env)
{
	char *str = "$a555$4";

	if (argv != 0)
		ac = 0;
	printf("%d %s\n", skip_redirect(str, 0, env), ft_dl_rpl_lvl2(str, 0, env));
	printf("22\n");
	return (0);
}
