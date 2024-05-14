/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:40:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/14 11:28:30 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_builtin(t_exec exec)
{
	if (!ft_strlen(exec.cmd))
		return (0);
	if (!ft_strcmp(exec.cmd, "exit"))
		on_exit(exec);
	if (!ft_strcmp(exec.cmd, "cd"))
		on_cd(exec);
	if (!ft_strcmp(exec.cmd, "pwd"))
		on_pwd(exec);
	if (!ft_strcmp(exec.cmd, "env"))
		on_env(exec);
	return (0);
}
