/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 22:54:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/17 15:43:38 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include <readline/readline.h> // Include readline header
# include <libft.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h> //for strerror
# include <sys/stat.h> //for stat, for dirs
# include <shared.h>
# include <mini.h>

typedef struct s_exec
{
	char			*cmd;
	int				argc;
	char			**argv;
	char			**env;
	int				exit_code;
}	t_exec;

// builtins
int				exec_builtin(t_exec exec);
t_exec	*simple_parse(char *line);

#endif
