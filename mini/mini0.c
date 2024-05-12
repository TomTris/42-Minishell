/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:07:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/12 11:00:56 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	mini0(t_mini *mini, char *str, char **env)
{
	mini->str = 0;
	mini->env = env;
	mini->sub_mini = 0;
	mini->str = str;
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_mini	mini;

	str = "1(2(3)4(5(6)7(8)9 1)2s34f5 )6|7 8|9 1c0d2|3|4a5b6 7s8f9f1 0%2%34 56\" 7'8\"";
	if (ac != 0)
		av = 0;
	if (ft_pre_check_syntax(str) == 0)
		return (printf("pre_check wrong\n"), 1);
	mini0(&mini, str, env);
	if (sub_mini0(&mini) == 0)
		return (1);
	return (0);
}