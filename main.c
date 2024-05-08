/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:19:34 by qdo               #+#    #+#             */
/*   Updated: 2024/05/08 05:33:25 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha_or__(char c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	ft_is_a_num(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ft_count_valid_characters_of_a_word(char *str)
{
	int	i;

	i = 0;
	if (str == 0 || ft_is_a_num(str[0]) == 1)
		return (0);
	while (str[i])
	{
		if (ft_isalpha_or__(str[i]) == 1 || ft_is_a_num(str[i] == 1))
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
	groups_break->new_input = 0;
}


//1. determine string is first step. it is so solid that we will destroy it at the end.
//2. determine "|", split them.
//3. determine input and output.
//4. determine " " - space, split them.
//5. determine $ and expand it.
//6. split again with " " - space
//7. dequote

int	ft_cnt_sub_str_for_new_input(char *str)
{
	
}

int	ft_break_input(char *str)
{
	int				i;
	t_groups_break	groups_break;
	int				num;

	ft_groups_break_init(&groups_break);
	groups_break.new_input = (char **)malloc
		((ft_cnt_sub_str_for_new_input(str) + 1 )* sizeof(char *));
	if (groups_break.new_input == 0)
		return (0);
	ft_fill_new_input(str);
}

int	main(int ac, char **av, char **env)
{
	t_save	save;

	if (ft_save_path_system_n_env_init(&save, env) == 0)
		return (1);
}
