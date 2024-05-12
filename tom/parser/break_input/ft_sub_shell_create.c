/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_shell_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:39:05 by qdo               #+#    #+#             */
/*   Updated: 2024/05/10 23:50:09 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_break_input.h"

static int	ft_cnt_sub(char *str)
{
	int	i;
	int	sub;

	i = -1;
	sub = 1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = ft_strchr(str + i + 1, str[i]) - str;
		if ((str[i] == '|' && str[i + 1] == '|')
			|| (str[i] == '&' && str[i + 1] == '&'))
		{
			sub++;
			i++;
		}
	}
	return (sub);
}

static char	*ft_sub_change_last(t_sub_shell *sub_shell, char *str, int nbr)
{
	char	*ret;

	sub_shell[nbr].str = ft_strdup(str);
	if (sub_shell[nbr].str == 0)
		return (0);
	ret = ft_strdup("");
	if (ret == 0)
		return (0);
	return (ret);
}

static char	*ft_sub_change(t_sub_shell *sub_shell, char *str, int nbr)
{
	int		i;
	char	*ret;

	if (nbr == sub_shell[0].nbr)
		return (ft_sub_change_last(sub_shell, str, nbr));
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '|' && str[i + 1] == '|')
			|| (str[i]) == '&' && str[i + 1] == '&')
		{
			sub_shell[nbr].str = ft_strndup(str, i);
			if (sub_shell[nbr].str == 0)
				return (0);
			sub_shell[nbr].sign_after = 2;
			if (str[i] == '|' && str[i + 1] == '|')
				sub_shell[nbr].sign_after = 1;
			sub_shell[nbr + 1].sign_before = 1;
			ret = ft_strdup(str + i + 2);
			if (ret == 0)
				return (0);
			return (ret);
		}
	}
	return (0);
}

static int	ft_sub_shell_default_value_init(t_sub_shell *sub_shell, int sub_cnt, char **env)
{
	int	i;

	i = -1;
	while (++i <= sub_cnt)
	{
		sub_shell[i].in_fd = STDIN_FILENO;
		sub_shell[i].out_fd = STDOUT_FILENO;
		sub_shell[i].nbr = i;
		sub_shell[i].sign_after = 0;
		sub_shell[i].sign_before = 0;
		sub_shell[i].str = 0;
		sub_shell[i].env = env;
	}
	sub_shell[0].nbr = sub_cnt;
	return (1);
}

t_sub_shell	*ft_sub_shell_pre_init(char *str, char **env)
{
	t_sub_shell	*sub_shell;
	int			i;
	char		*temp;
	int			sub_cnt;

	sub_cnt = ft_cnt_sub(str);
	sub_shell = (t_sub_shell *)malloc((sub_cnt + 1) * sizeof(t_sub_shell));
	if (sub_shell == 0)
		return (free(str), 0);
	ft_sub_shell_default_value_init(sub_shell, sub_cnt, env);
	i = 0;
	while (++i <= sub_cnt)
	{
		temp = str;
		str = ft_sub_change(sub_shell, str, i);
		free(temp);
		if (str == 0)
			return (ft_free_sub_shell(sub_shell), 0);
	}
	free(str);
	return (sub_shell);
}
