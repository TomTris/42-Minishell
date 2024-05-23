/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:44:19 by qdo               #+#    #+#             */
/*   Updated: 2024/05/22 10:42:30 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//not free str
// ret[0] = 0 -> an empty string
// ret[0] == 2 -> $rggf -> abigious
static int	ft_ambigious_0(char *str, char **env)
{
	int	i;
	int	j;

	if (str[0] != '$')
		return (0);
	if (ft_isdigit(str[1]) == 1 || ft_isalnum_(str[1]) != 1 || str[1] == 0)
		return (0);
	i = 2;
	while (str[i])
	{
		if (ft_isalnum_(str[i]) != 1)
			return (0);
		i++;
	}
	j = -1;
	while (env[++j])
	{
		if (sncmp(env[j], str + 1, i - 1) == 1
			&& env[j][i - 1] == '=' && env[j][i - 1] != '\0')
			return (0);
	}
	return (1);
}

static int	get_nbr(char *str)
{
	int	ret;
	int	i;

	ret = 1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ret || ft_isempty(ret) == 1)
		{
			i = -1;
			ret++;
		}
	}
	return (ret);
}

void	ft_change_star(char *str, int nbr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += ft_strchr(str + 1, str[i]) - str + 1;
		else if (str[i] == '*')
			str[i] = nbr;
		else
			i++;
	}
}

// if there is nothing left -> ret[0] = NULL, like < $aaafeff or nothing.
// if it's like "" -> ret[0][0] = 0, ret[1] = 0.
char	**str_replace(char *str_ori, char **env)
{
	int		nbr;
	char	*str;
	char	**str2;
	char	**ret;

	if (ft_ambigious_0(str_ori, env) == 1)
		return (smerge(0, 0));
	str = ft_strdup(str_ori);
	if (str == 0)
		return (exit_code(1), perror("ft_strdup"), NULL);
	nbr = get_nbr(str);
	ft_change_star(str, nbr);
	str2 = dollar_handler(str, env, nbr);
	free(str);
	if (str2 == NULL)
		return (NULL);
	ret = merge_with_wildcard(str2, nbr);
	free_split(str2);
	if (ret == 0)
		return (NULL);
	return (ret);
}

// // ambigious or ret = str_replace("", env) -> ret[0] = NULL
// // ret = str_replace("\"\"") or ("\'\'") -> ret[0][0] = '\0'
// int	main(int ac, char **av, char **env)
// {
// 	char	**ret;
// ac = 0;
// av = 0;
// 	printf("--------------------\n\n\n\n\n\n");
// 	ret = str_replace("$3", env);
// 	printf("ret[0] = {%s}\n", ret[0]);
// 	// printf("str = {%s}\n", ret[0]);
// 	while (ret[ac])
// 	{
// 		printf("%s \n", ret[ac++]);
// 	}
// 	// printf("\n");
// 	free_split(ret);
// 	ret = 0;
// 	// system("leaks mini");
// 	return (0);
// }

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// char	**make_env(char **env)
// {
// 	char	**ret;
// 	int		i;

// 	ret = smerge(0, 0);
// 	if (ret == 0)
// 		return (0);
// 	i = -1;
// 	while (env[++i])
// 	{
// 		ret = smerge(ret, env[i]);
// 		if (ret == 0)
// 			return (0);
// 	}
// 	return (ret);
// }

// int	main(int ac, char **av, char **env_ori)
// {
// 	char	*str;
// 	char	**env;
// 	char	**str_rpl;
// 	int		i;

// ac = 0;
// av = 0;
// 	str = "\"$HOME'$HOME'\"";
// 	env = make_env(env_ori);
// 	if (env == 0)
// 		return (0);
// 	str_rpl = str_replace(str, env);
// 	if (str_rpl == 0)
// 		return (free_split(env), 0);
// 	i = -1;
// 	// printf("%s\n", str_rpl[0]);
// 	while (str_rpl[++i] != 0)
// 		printf("%s ", str_rpl[i]);
// 	printf("\n");
// 	free_split(env);
// 	free_split(str_rpl);
// 	return (0);
// }
