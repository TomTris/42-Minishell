/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:22:13 by qdo               #+#    #+#             */
/*   Updated: 2024/05/14 17:20:22 by qdo              ###   ########.fr       */
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
