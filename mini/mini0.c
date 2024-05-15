/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:07:23 by qdo               #+#    #+#             */
/*   Updated: 2024/05/15 23:25:36 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// char	*make_input(int ac, char **av)
// {
// 	char	*str2;
// 	char	*str1;
// 	char	*temp;
// 	int		i;

// 	if (ac == 1)
// 		return (printf("put input\n"), NULL);
// 	str1 = ft_strdup(av[1]);
// 	if (str1 == 0)
// 		return (perror("ft_strdup"), NULL);
// 	i = 1;
// 	while (av[++i])
// 	{
// 		temp = str1;
// 		str2 = ft_strdup(av[i]);
// 		if (str2 == 0)
// 			return (free(temp), perror("ft_strdup"), NULL);
// 		str1 = ft_strjoin(str2, temp);
// 		free(temp);
// 		free(str2);
// 		if (str1 == 0)
// 			return (perror("ft_strjoin"), NULL);
// 	}
// 	return (str1);
// }

char	**make_env(char **env)
{
	char	**ret;
	int		i;

	ret = smerge(0, 0);
	if (ret == 0)
		return (0);
	i = -1;
	while (env[++i])
	{
		ret = smerge(ret, env[i]);
		if (ret == 0)
			return (0);
	}
	return (ret);
}

t_mini	*mini0(char *str, char ***env, int lvl)
{
	t_mini	*mini;

	if (str == 0)
		return (perror("s1ndup"), NULL);
	mini = (t_mini *)malloc(1 * sizeof(t_mini));
	if (mini == 0)
		return (perror("Malloc failed"), free(str), NULL);
	mini->env = env;
	mini->sub_mini = 0;
	mini->str = str;
	mini->lvl = lvl;
	mini->fd_heredoc = -1;
	if (sub_mini0(mini) == 0)
	{
		free_mini(mini);
		free(mini);
		return (0);
	}
	return (mini);
}

//heredoc delete - only ctrl D // exit.
int	ft_clean_programm(t_mini *mini_outside, int exit_nbr, int leaks_check)
{
	static t_mini	*mini = NULL;

	if (mini_outside != 0)
	{
		mini = mini_outside;
		return (1);
	}
	else
	{
		if (mini->env != 0)
			free_split(*(mini->env));
		free_mini(mini);
		free(mini);
		if (leaks_check != 0)
			system("leaks mini");
		exit(exit_nbr);
		return (1);
	}
}

int	*ft_fd_heredoc_default(int fd_new)
{
	int	*fd;

	fd = (int *)malloc(2 * sizeof(int));
	if (fd == NULL)
	{
		print_err("malloc failed fd_create_fd_heredoc");
		return (NULL);
	}
	fd[0] = 1;
	fd[1] = fd_new;
	return (fd);
}

int	*ft_fd_add(int *fd, int fd_new)
{
	int	i;
	int	*fd_arr_new;

	fd_arr_new = (int *)malloc((fd[0] + 2) * sizeof(int));
	if (fd_arr_new == NULL)
	{
		i = 0;
		while (++i <= fd[0])
			close(fd[i]);
		return (NULL);
	}
	fd_arr_new[0] = fd[0] + 1;
	i = 0;
	while (++i <= fd[0])
		fd_arr_new[i] = fd[i];
	fd_arr_new[i] = fd_new;
	free(fd);
	return (fd_arr_new);
}

int	ft_fd_heredoc(int fd_new)
{
	static int	*fd = 0;
	int			i;

	if (fd == 0)
	{
		fd = ft_fd_heredoc_default(fd_new);
		if (fd == 0)
			return (-1);
		return (fd_new);
	}
	if (fd_new == -1)
	{
		i = 0;
		while (++i <= fd[0])
			close(fd[i]);
		return (-1);
	}
	fd = ft_fd_add(fd, fd_new);
	if (fd == NULL)
		return (-1);
	return (fd_new);
}

int	ft_lvl_cnt(int lvl_outside)
{
	static int	lvl = 0;

	if (lvl_outside > lvl)
		lvl = lvl_outside;
	return (lvl);
}

void	ft_init_heredoc(t_mini *mini)
{
	unlink(HERE_DOC_FILE);
	mini->fd_heredoc = open(HERE_DOC_FILE, O_CREAT, 0644);
	if (mini->fd_heredoc == -1)
		ft_clean_programm(0, 1, 0);
}

int	main(int ac, char **av, char **env_ori)
{
	t_mini	*mini;
	char	*str;
	char	**env;

	(void)ac;
	(void)av;
	str = "(<0(<1(<2(<3(1)) ) >3 )>4) >8";
	if (ft_isclosed(str) == 0)
		return (1);
	mini = mini0(sndup(str, ft_strlen(str)), 0, 1);
	if (mini == 0)
		return (0);
	ft_clean_programm(mini, 0, 0);
	env = make_env(env_ori);
	if (env == 0)
		return (ft_clean_programm(0, 1, 0));
	mini->env = &env;
	// ft_init_heredoc(mini);
	// if (ft_break_input(mini) == 0)
	// 	print_err("break input sthwrong\n");
	ft_clean_programm(0, 0, 0);
	return (0);
}
