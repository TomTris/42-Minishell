/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:40:14 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/20 13:36:56 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_builtin(t_exec e)
{
	if (!ft_strlen(e.argv[0]))
		return (0);
	if (!scmp(e.argv[0], "exit"))
		on_exit(e);
	if (!scmp(e.argv[0], "cd"))
		on_cd(e);
	if (!scmp(e.argv[0], "pwd"))
		on_pwd(e);
	if (!scmp(e.argv[0], "env"))
		on_env(e);
	if (!scmp(e.argv[0], "export"))
		on_export(e);
	if (!scmp(e.argv[0], "echo"))
		on_echo(e);
	if (!scmp(e.argv[0], "unset"))
		on_unset(e);
	return (0);
}
