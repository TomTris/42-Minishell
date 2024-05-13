/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:07:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/13 23:56:11 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_mini	*mini0(char *str, char ***env, int lvl)
{
	t_mini	*mini;

	if (str == 0)
		return (perror("sndup"), NULL);
	mini = (t_mini *)malloc(1 * sizeof(t_mini));
	if (mini == 0)
		return (perror("Malloc failed"), free(str), NULL);
	mini->env = env;
	mini->sub_mini = 0;
	mini->str = str;
	mini->lvl = lvl;
	if (sub_mini0(mini) == 0)
	{
		free_mini(mini);
		free(mini);
		return (0);
	}
	return (mini);
}

void	mini_empty(t_mini *mini)
{
	mini->env = 0;
	mini->sub_mini = 0;
	mini->str = 0;
}

// int	main(int ac, char **av, char **env)
// {
// 	// char	*str = "1 |< 1( <3 ||(23) && (<1 () || 2) <<2>4| <3 (1|7) | <8)|9 ||1c0d2| 2";
// 	t_mini	*mini;
// 	// char	*str = " ((1)||<$|(<2(A|>4))&&1>3|4)||(2)  > ||  |  ";
// 	// ft_strcpy(str,
// 	// 	 "1(2(3)4(5(6)7(8)9 1)2s34f5 )6|7 8|9 ||1c0d2|3|4a5b6 7s8f9f1 0%2%34 56\" 7'8\"");
// 	// ft_strcpy(str, "1 |<(23)46|7 8|9 ||1c0d2|");
// 	// ft_strcpy(str, "1 |< 1((23) |7 8)|9 ||1c0d2| 2");
// 	char	*str = "(s) <  (a)";
// 	if (ac != 0)
// 		av = 0;
// 	if (ft_isclosed(str) == 0)
// 		return (printf("pre_check wrong\n"), 0);
// 	env = 0;
// 	mini = mini0(ft_strdup(str), 0, 0);
// 	if (mini == 0)
// 		return (print_err("sth wrong"), 0);
// 	printf("\ngood input\n");
// 	free_mini(mini);
// 	free(mini);
// 	mini = 0;
// 	// system("leaks mini");
// 	// mini_empty();
// 	// system("leaks mini");
// 	return (0);
// }
