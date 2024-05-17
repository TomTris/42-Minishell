/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:14:22 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/17 17:41:35 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

// TODO:validate if exit arg valid int
int	is_valid_int(char *arg)
{
	(void)arg;
	return (1);
}

void	print_prompt(void)
{
	printf("minishell: ");
}

void	ft_sort_ascii(char **ret)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (ret[i])
		i++;
	while (i-- > 1)
	{
		j = 0;
		while ((j + 1) <= i - 1)
		{
			if (ft_strncmp(ret[j], ret[j + 1], ft_strlen(ret[i]) + 1) > 0)
			{
				temp = ret[j];
				ret[j] = ret[j + 1];
				ret[j + 1] = temp;
			}
			j++;
		}
	}
}
