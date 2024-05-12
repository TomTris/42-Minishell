/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:19:34 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 15:03:26 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_valid_characters_of_a_word(char *str)
{
	int	i;

	i = 0;
	if (str == 0 || ft_isdigit(str[0]) == 1)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			i++;
		else
			return (i);
	}
}

void	ft_groups_break_init(t_groups_break *groups_break)
{
	ft_strcpy(groups_break->and_sign, "&&");
	ft_strcpy(groups_break->doublequote, "\"");
	ft_strcpy(groups_break->or_sign, "&&");
	ft_strcpy(groups_break->parenthesis_close, "(");
	ft_strcpy(groups_break->parenthesis_open, ")");
	ft_strcpy(groups_break->pipe_sign, "|");
	ft_strcpy(groups_break->singlequote, "'");
}


int	ft_cmp_rl_n_groups(char *rl, t_groups_break *groups_break)
{
	if (ft_strncmp(rl, groups_break->and_sign, 2) == 0)
		return (4);
	if (ft_strncmp(rl, groups_break->or_sign, 2) == 0)
		return (3);
	if (ft_strncmp(rl, groups_break->doublequote, 1) == 0)
		return (1);
	if (ft_strncmp(rl, groups_break->singlequote, 1) == 0)
		return (2);
	if (ft_strncmp(rl, groups_break->parenthesis_close, 1) == 0)
		return (7);
	if (ft_strncmp(rl, groups_break->parenthesis_open, 1) == 0)
		return (8);
	if (ft_strncmp(rl, groups_break->pipe_sign, 1) == 0)
		return (5);
	return (0);
}

//1. determine "" and is first step. it is so solid that we will destroy it at the end.
//2. determine "|", split them.
//3. determine input and output.
//4. determine " " - space, split them.
//5. determine $ and expand it.
//6. split again with " " - space
//7. dequote

// int	ft_skip()

int	ft_cnt_sub_str_for_new_input(char *rl, t_save *save)
{
	int	i;
	int	check_skip;
	int	ret;
	int	check;

	ret = 1;
	i = 0;
	while (rl[i])
	{
		check = ft_cmp_rl_n_groups(rl, &(save->groups_break));
		if (check == 3 || check == 4 || check == 5)
		{
			ret++;
			if (check == 3 || check == 4)
				i += 2;
		}
		else if (check == 7)
			return (write
				(2, "bash: syntax error near unexpected token `)'", 24), 0);
		else if (check > 0)
		{
			check_skip = ft_skip(rl[i + 1], check, save);
			if (check_skip == -1 && (check == 1 || check == 2))
				return (write(2, "invalid quote\n", 14), 0);
			if (check_skip == -1 && (check == 6 || check == 7))
				return (write(2, "invalid quote\n", 14), 0);
		}
		else
			i++;
	}
	return (ret);
}

int	ft_break_input(char *str, t_save *save, t_groups_break *groups_break)
{
	int				i;
	int				num;

	ft_groups_break_init(groups_break);
	num = (ft_cnt_sub_str_for_new_input(str, save) + 1);
	save->input_break = (char **)malloc(num * sizeof(char *));
	if (save->input_break == 0)
		return (0);
	ft_fill_new_input(str);
}

int	main(int ac, char **av, char **env)
{
	t_save	save;
	char	*rl;

	if (ft_save_path_system_n_env_init(&save, env) == 0)
		return (1);
	ft_break_input(rl ,&save, &save.groups_break);
}
