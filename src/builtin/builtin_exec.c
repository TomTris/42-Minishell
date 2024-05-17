/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:40:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/17 14:59:16 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_builtin(t_exec exec)
{
	if (!ft_strlen(exec.cmd))
		return (0);
	if (!scmp(exec.cmd, "exit"))
		on_exit(exec);
	if (!scmp(exec.cmd, "cd"))
		on_cd(exec);
	if (!scmp(exec.cmd, "pwd"))
		on_pwd(exec);
	if (!scmp(exec.cmd, "env"))
		on_env(exec);
	if (!scmp(exec.cmd, "export"))
		on_export(exec);
	if (!scmp(exec.cmd, "echo"))
		on_echo(exec);
	if (!scmp(exec.cmd, "unset"))
		on_unset(exec);
	return (0);
}
