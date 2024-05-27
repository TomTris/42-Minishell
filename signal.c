/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:38:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/27 01:35:33 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_sig_2(int sig)
{
	exit_code((sig + 128) % 256);
	ft_clean_programm(0, 1);
}

void	sigint_handler1(int sig)
{
	exit_code((sig + 128) % 256);
	rl_replace_line("", 1);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler2(int sig)
{
	exit_code((sig + 128) % 256);
	rl_replace_line("", 1);
	printf("\n");
	rl_on_new_line();
}

void	ft_sig_heredoc(int sig)
{
	ft_ctrl_c(1);
	exit_code((sig + 128) & 256);
}
