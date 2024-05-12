/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_shell_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:43:39 by qdo               #+#    #+#             */
/*   Updated: 2024/05/10 23:46:48 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_break_input.h"

//return value i
//=> str[i] != empty,
int	ft_empty_cnt_and_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i += ft_empty_cnt(str);
		if (str[i] == '\'' || str[i] == '"')
			i += ft_strchr(str + i + 1, str[i]) - str + 1;
		else
			return (i);
	}
	return (i);
}

char	*ft_handle_here_doc2(char *str, int *j)
{
	int		here_doc_len;
	char	*ret;
	int		i;

	i = *j + 2;
	i += ft_empty_cnt(str + i);
	if ()
	here_doc_len = ft_cnt_valid_word(str);
	ret = ft_strndup(str + i, here_doc_len);
	if (ret == 0)
		return (0);
}

char	*ft_handle_here_doc1(char *str_ori)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	str = ft_dup(str_ori);
	if (str == 0)
		return (0);
	while (str[i])
	{
		i += ft_empty_cnt_and_quotes(str + i);
		if (str[i] == '<' && str[i + 1] == '<')
		{
			temp = str;
			str = ft_handle_here_doc2(str, &i);
			if (str == 0)
				return (free(temp), 0);
		}
		else
			i++;
	}
	return (str);
}

char	*ft_handle_in_out_fd(char *str_ori)
{
	int		i;
	char	*str1;
	char	*str2;

	str1 = ft_handle_here_doc1(str_ori);
	if (str1 == 0)
		return (0);
	str2 = ft_hanle_redirect(str1);
	free(str1);
	return (str2);
}

int	ft_no_pipe(char *str)
{
	pid_t	pid;
	int		status;
	int		check_fnc;
	char	str_left;

	pid = fork();
	if (pid == -1)
		return (ft_printf_fd(2, "fork failed\n"), 0);
	if (pid == 0)
	{
		str_left = ft_handle_in_out_fd(str);
		if (str_left == 0)
			return (0);
		return (ft_execute_handle(str), -99);
	}
	if (wait(&status) == -1)
		return (perror("wait"), 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (0)
}

//good return 1, else 0
int	ft_sub_shell_execute(t_sub_shell sub_shell)
{
	int		i;
	int		status;
	pid_t	pid;

	i = ft_cnt_pipe();
	if (i++ == 0)
		return (ft_no_pipe(str));
	
}
