/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mini_unit_redi.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:00:58 by qdo               #+#    #+#             */
/*   Updated: 2024/05/18 03:39:50 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_redi_execute_heredoc(t_mini_unit *mini_unit)
{
	int	i;

	i = 0;
	if (mini_unit->fd_heredoc != NULL)
	{
		while (++i <= mini_unit->fd_heredoc[0])
		{
			if (dup2(mini_unit->fd_heredoc[i], STDIN_FILENO) == -1)
				return (perror("dup2"), 0);
		}
	}
	return (1);
}

int	ft_redi_execute_redi2(t_redirection *redi, int fd_redi)
{
	int	i;
// dprintf(2, "get in\n");
	if (fd_redi == -1)
		return (dprintf(2, "getout!\n"), perror(redi->str), 0);
	if (redi->type_re == RE_IN)
		i = dup2(fd_redi, STDIN_FILENO);
	else
		i = dup2(fd_redi, STDOUT_FILENO);
	if (redi->type_re == RE_IN)
	{
		// dprintf(2, "wtf?");
		close(fd_redi);
		// printf("1\n");
	}
	else if (redi->type_re != RE_IN)
	{
		// dprintf(2, "fd_redi = %d\n", fd_redi);
		ft_fd_out(fd_redi);
		// dprintf(2, "done save\n");
	}
	// else
	// 	dprintf(2, "???\n");
	if (i == -1)
		return (perror("dup2"), 0);
	return (1);
}

int	ft_redi_execute_redi(t_redirection *redi, char **env)
{
	int		fd_redi;
	char	**str;
	char	*str2;

	str = str_replace(redi->str, env);
	if (str == 0)
		return (perror("str_replace"), 0);
	if (str[0] == NULL || str[1] != 0)
		return (print_fd(2, "%s: ambigious redirect\n",
				redi->str), free_split(str), 0);
	str2 = str[0];
	free(str);
	if (redi->type_re == APPEND)
		fd_redi = open(str2, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (redi->type_re == RE_OUT)
		fd_redi = open(str2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
	{
		// if (redi->type_re == RE_IN)
			// printf("true\n\n");
		fd_redi = open(str2, O_RDONLY, 0644);
		// printf("str = %s\n", redi->str);
		// printf("type = %d\n", redi->type_re);
	}
	printf("fd infile  = %d\n", fd_redi);
	free(str2);
	return (ft_redi_execute_redi2(redi, fd_redi));
}

int	ft_redi_execute(t_mini_unit *mini_unit)
{
	int	i;

	ft_redi_execute_heredoc(mini_unit);
	if (mini_unit->redi != 0)
	{
		i = 0;
		while (++i <= mini_unit->redi[0].type_re)
		{
			if (ft_redi_execute_redi(
					&(mini_unit->redi[i]), *(mini_unit->env_ori)) == 0)
				break ;
		}
		if (i == mini_unit->redi[0].type_re + 1)
			return (1);
		return (0);
	}
	return (1);
}