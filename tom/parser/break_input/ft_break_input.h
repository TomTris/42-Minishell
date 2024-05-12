/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_break_input.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:04:22 by qdo               #+#    #+#             */
/*   Updated: 2024/05/10 23:50:28 by qdo              ###   ########.fr       */
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
	char	**env;
}	t_sub_shell;



void		ft_free_sub_shell(t_sub_shell *sub_shell);
t_sub_shell	*ft_sub_shell_pre_init(char *str, char **env);
int			ft_sub_shell_execute(t_sub_shell sub_shell);

#endif