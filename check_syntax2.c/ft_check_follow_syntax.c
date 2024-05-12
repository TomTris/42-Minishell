/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_follow_syntax.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:39:22 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 21:27:21 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	start_check(char *str, char **env);

//plus this func -> to the new char, not a part of $_replace
int	skip_after_dl_rpl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '&')
				i++;
			else if (ft_isdigit(str[i + 1]) == 1)
				i = i + 2;
			else
			{
				while (ft_isalnum_(str[i]) == 1)
					i++;
			}
		}
		else
			return (i + 1);
	}
	return (1);
}

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

int	print_syn_err(char *str, int i, int len)
{
	char	*temp;
	int		check;

	if (len <= 0)
	{
		if (str[i] == '&' && str[i + 1] == '&')
			check = ft_printf_fd(2, "syntax error near unexpected token `&&'\n");
		else if (str[i] == '|' && str[i + 1] == '||')
			check = ft_printf_fd(2, "syntax error near unexpected token `||'\n");
		else if (str[i] == '|')
			check = ft_printf_fd(2, "syntax error near unexpected token `|'\n");
		else
			check = ft_printf_fd(2, "wrong usage of print syn eror\n");
		if (check == -1)
			return (perror("ft_printf_fd\n"), 0);
	}
	temp = (char *)malloc((len + 1) * sizeof(char));
	if (temp == 0)
		return (perror("Malloc failed\n"), 0);
	temp[len] = 0;
	while (--len >= 0)
		temp[len] = str[i + len];
	if (ft_printf_fd(2, "syntax error near unexpected token `%s'\n", temp) == -1);
		return (free(temp), perror("ft_printf_fd\n"), 0);
	return (free(temp), 0);
}

// This func checksonly after closed.
// Failed: return 0. When? after closed parenthesis,
// there should be only proper redirections or signs | || &&,
// Suucess: return the place of the closed parent.
// How to use?
// having str 012(45)
// return value: 6, sothat str[i + paren_closed_find(str + 4)] = 6
int	parent_closed_find(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = strchr(str + i + 1, str[i]) - str;
		else if (str[i] == ')')
			return (i + 1);
		else if (str[i] == '(')
			i += parent_closed_find(str + i + 1);
	}
	return (0);
}

int	check_after_parent(char *str, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		while (ft_isempty(str[i]) != 0 && str[i])
			i++;
		if (str[i] == '<' || str[i] == '>')
		{
			j = check_n_skip_redirect(str + i, env);
			if (j == 0)
				return (0);
			i += j;
		}
		else if (str[i] == ')' || str[i] == '|'
			|| (str[i] == '&' && str[i + 1] == '&'))
			return (i + 1);
		else
		{
			j = 0;
			while (str[i + j] && ft_isempty(str[i + j]) != 1)
				j++;
			return (print_syn_err());
		}
	}
	return (i + 1);
}

int	check_parent(char *str, int i, char **env)
{
	int	i;
	int	check;
	int	check2;

	i = parent_closed_find(str + 1);
	check = start_check(str + 1, env);
	if (check == 0)
		return (0);
	check2 = check_after_parent(str + i + 1, env);
	if (check2 == 0)
		return (0);
	return (i + check2);
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
			return (perror("ft_strdup"), 0);
		return (ret);
	}
	j = 1;
	while (ft_isalnum_(str[i + j]) != 1)
		j++;
	ret = ft_strndup(str[i], j);
	if (ret == 0)
		return (perror("ft_strdup"), 0);
	i = -1;
	while (env[++i])
	{
		j = ft_strlen(ret);
		if (ft_strncmp(ret, env[i], j) == 0 && env[i][j] == '=')
		{
			free(ret);
			ret = ft_strdup(env[i] + j + 1);
			if (ret == 0)
				return (perror("ft_strdup"), 0);
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

	ret = ft_strdup("");
	if (ret == 0)
		return (perror("ft_strdup\n"), 0);
	while (str[i] == '$')
	{
		temp = ft_dl_rpl_cre(str, i, env);
		if (temp == 0)
			return (free(ret), 0);
		temp2 = ret;
		ret = ft_strjoin(temp2, temp);
		free(temp);
		free(temp2);
		if (ret == 0)
			return (perror("ft_strjoin"), 0);
		i = ft_dl_skip_lvl1(str, i);
	}
	return (ret);
}

int	ft_dl_skip_lvl1(char *str, int i)
{
	while (str[i] == '$')
		i++;
	if (ft_isdigit(str[i++]) == 1)
		return (i);
	while (ft_isalnum_(str[i]) == 1)
		i++;
	return (i);
}

int	ft_dl_skip_lvl2(char *str, int i)
{
	while (ft_isempty(str[i]) != 0 && str[i] && token_check(str[i]) == 0)
	{
		if (str[i] == '"' || str[i] == '\'')
			i = ft_strchr(str + i + 1, str[i]) - str + 1;
		else if (str[i] == '$')
			i = ft_dl_skip_lvl1(str, i);
	}
	return (i);
}


int	check_n_skip_redirect(char *str, int i, char **env)
{
	char	*check;

	check = ft_dl_rpl_lvl2(str, i, env);
	if (check == 0)
		return (0);
	if (check[0] == 0)
	{
		if (ft_printf_fd(2, "syntax error near unexpected token `||'\n") == -1)
			perror("ft_printf_fd");
		return (0);
	}
	free(check);
	return (ft_dl_skip_lvl2(str, i));
}

int	main(int ac, char **argv, char **env)
{
	char *str = "<3a5554";

	if (argv != 0)
		ac = 0;
	printf("%d %s", check_n_skip_redirect(str, 0, env), ft_dl_rpl_lvl2(str, 0, env));
	return (0);
}


//check2 only for re
//check3: there is already ()
//check1: there is already anythings else (not redirection, not () );
int	start_check(char *str, char **env, int check3)
{
	int	i;
	int	j;
	int	check1;
	int	check2;

	i = 0;
	check1 = 0;
	check2 = 0;
	while (str[i])
	{
		while (ft_isempty(str[i]) == 1 && str[i])
			i++;
		if (str[i] == ')')
		{//return to after ')'
			if (check1 == 0 && check2 == 0 && check3 == 0)
				return (0);
			return (i + 1);
		}
		else if (str[i] == '\'' || str[i] == '"')
		{
			check1 = 1;
			i = ft_strchr(str + i + 1, str[i]) - str + 1;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			check2 = 1;
			i = check_n_skip_redirect(str, i, env);
			if (i == 0)
				return (0);
		}
		else if (str[i] == '(')
		{
			if (check3 != 0 || check1 != 0)
				return (print_syn_err(str, i, 1));
			i = check_parent(str, i, env);
			if (i == 0)
				return (0);
		}
		else if (str[i] == '|' || (str[i] == '&' && str[i + 1] == '&'))
		{
			if (check1 == 0 && check2 == 0 && check3 == 0)
				return (print_syn_err(str, i, 0));
			check1 = 0;
			check2 = 0;
			check3 = 0;
			i++;
			if (str[i] == '&' || str[i + 1] == '|')
				i++;;
		}
		else
		{
			if (check3 == 1)
			{
				j = 0;
				while (ft_isempty(str[i + j]) && str[i + j] != 0)
					j++;
				return (print_syn_err(str, i, j));
			}
			check1 = 1;
			i++;
		}
	}
	printf("finished\n");
	return (1);
}

// int	main(int ac, char **argv, char **env)
// {
// 	char *str = "(ac) <3";

// 	if (argv != 0)
// 		ac = 0;
// 	if (ft_pre_check_syntax(str) == 0)
// 		return (printf("somewhere wrong 1\n"), 1);
// 	if (start_check(str, env) == 0)
// 		return (printf("somewhere wrong 1\n"), 1);
// 	return (0);
// }
