/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:00:33 by qdo               #+#    #+#             */
/*   Updated: 2024/05/12 10:32:45 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../libft/libft.h"
# include <dirent.h> //opendir


# define OR 1
# define AND 2
# define PIPE 3
# define O_PARENT 4
# define CLO_PARENT 5
# define RE_IN 6
# define RE_OUT 7
# define HERE_DOC 8
# define APPEND 9

typedef struct s_mini	t_mini;
//sign 0 nothing
//sign 1 = <
//sign 2 = >
//sign 3 = <<
//sign 4 = >>

typedef struct s_mini_unit
{
	int			nbr;
	char		*str;
	char		*cmd;
	char		**args;
	char		**re_in;
	char		**re_out;
	char		**here_doc;
	char		**append;
	char		***env_ori;
	t_mini		*mini;
}	t_mini_unit;

typedef struct s_sub_mini
{
	int			nbr;
	int			sign_after;
	char		*str;
	char		***env_ori;
	t_mini_unit	*mini_unit;
}	t_sub_mini;

typedef struct s_mini
{
	char		*str;
	char		**env;
	t_sub_mini	*sub_mini;
}	t_mini;

int	ft_pre_check_syntax(char *str);


int				mini_unit0(t_sub_mini *sub_mini);
void			mini0(t_mini *mini, char *str, char **env);
int				sub_mini0(t_mini *mini);

int				ft_free_mini(t_mini *mini);
int				ft_free_sub_mini(t_sub_mini **sub_mini_ori);
int				ft_free_mini_unit(t_mini_unit **mini_unit_ori);


int				after_quote(char *str);
int				token(char *str);
int				print_err(char *str);
int				after_1_parent(char *str);
int				after_mlt_parent(char *str);

#endif