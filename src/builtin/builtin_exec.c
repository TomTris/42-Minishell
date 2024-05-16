/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:40:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/16 15:28:46 by bpisak-l         ###   ########.fr       */
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
	if (!ft_strcmp(exec.cmd, "export"))
		on_export(exec);
	if (!ft_strcmp(exec.cmd, "echo"))
		on_echo(exec);
	return (0);
}
