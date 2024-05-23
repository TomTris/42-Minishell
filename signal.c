/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:38:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/23 09:13:25 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_sig_2(int sig)
{
	if (sig == SIGINT)
		exit_code(130);
	else
		exit_code(131);
	ft_clean_programm(0, 1);
}

void	sigint_handler1(int sig)
{
	exit_code(sig + 128);
	rl_replace_line("", 1);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}
//   char    *temp;
// (void)sig;
// temp = ft_strjoin(rl_line_buffer, "  ");
// rl_replace_line(temp, 0);
// free(temp);
// rl_redisplay();
// ft_putchar_fd('\n', STDOUT_FILENO);
// rl_on_new_line();
// rl_replace_line("", 0);
// rl_redisplay();

void	sigint_handler2(int sig)
{
	exit_code(sig + 128);
	rl_replace_line("", 1);
	printf("\n");
	rl_on_new_line();
}
//   char    *temp;
// (void)sig;
// temp = ft_strjoin(rl_line_buffer, "  ");
// rl_replace_line(temp, 0);
// free(temp);
// rl_redisplay();
// ft_putchar_fd('\n', STDOUT_FILENO);
// rl_on_new_line();
// rl_replace_line("", 0);
// rl_redisplay();

void	sigint_handler3(int sig)
{
	exit_code(sig + 128);
}
