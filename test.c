/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:22:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/17 14:34:48 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	int	i;

ac = 0;
av = 0;
	char **a = (char **)malloc(5 * sizeof(char *));
	a[0] = (char *)"ls";
	a[1] = NULL;
	
	execve(NULL, NULL, env);
	perror("");
	printf("5\n");
	return (1);
}
