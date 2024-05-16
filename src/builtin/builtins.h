/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:39:48 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/16 15:33:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <minishell.h>

void	on_exit(t_exec e);
void	on_cd(t_exec e);
void	on_pwd(t_exec e);
void	on_env(t_exec e);
void	on_export(t_exec e);
void	on_echo(t_exec e);

#endif