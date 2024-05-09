/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_break_input.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:04:22 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 22:15:20 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BREAK_INPUT.H
# define FT_BREAK_INPUT.H

#include "../../libft/libft.h"

typedef struct s_sub_shell
{
	int		in_fd;
	int		out_fd;
	int		nbr;
	int		sign_before;
	int		sign_after;
	char	*str;
}	t_sub_shell;


t_sub_shell	*ft_sub_shell_create(char *str);
int			ft_sub_shell_process(t_sub_shell *sub_shell);
void		ft_free_sub_shell(t_sub_shell *sub_shell);


#endif