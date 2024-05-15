/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:00:33 by qdo               #+#    #+#             */
/*   Updated: 2024/05/15 23:50:41 by qdo              ###   ########.fr       */
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
# define C_PARENT 5
# define RE_IN 6
# define RE_OUT 7
# define HERE_DOC 8
# define APPEND 9
# define NEWLINE 10

# define HERE_DOC_FILE ".heredoc.Qdo&&Bori@42Heilbronn.de"

typedef struct s_mini	t_mini;
//sign 0 nothing
//sign 1 = <
//sign 2 = >
//sign 3 = <<
//sign 4 = >>

typedef struct s_redirection
{
	int		fd;
	int		type_re;
	char	*str;
}	t_redirection;

typedef struct s_fd_heredoc
{
	int		fd;
	char	*limiter;
}	t_fd_heredoc;

typedef struct s_mini_unit
{
	int				nbr;
	int				nbr_sum;
	int				lvl;
	char			*str;
	char			**cmd;
	char			**args;
	t_redirection	*redi;
	char			***env_ori;
	int				sign_sub;
	t_mini			*mini;
}	t_mini_unit;

typedef struct s_sub_mini
{
	int			nbr;
	int			sign_after;
	int			lvl;
	char		*str;
	char		***env_ori;
	t_mini_unit	*mini_unit;
}	t_sub_mini;

typedef struct s_mini
{
	char		*str;
	char		***env;
	int			lvl;
	int			fd_heredoc;
	t_sub_mini	*sub_mini;
}	t_mini;


/*************************Mini created *********************************/
t_mini			*mini0(char *str, char ***env, int lvl);
int				sub_mini0(t_mini *mini);
int				mini_unit0(t_sub_mini *sub_mini);
int				ft_lvl_cnt(int lvl_outside);
/*************************Syntax check *********************************/

int				syntax_check(t_mini_unit *mini_unit, char *str);

int				free_mini(t_mini *mini);
int				free_split(char **to_free2);
// int				free_sub_mini(t_sub_mini *sub_mini);
// int				free_mini_unit(t_mini_unit *mini_unit);

//ft_is_closed
int				ft_isclosed(char *str);

//freq_used.c
int				after_quote(char *str);
int				token(char *str);
int				print_err(char *str);
int				after_1_parent(char *str);
int				after_mlt_parent(char *str);

//freq_used2.c
int				syn_err(char *str, int sign);
char			**smerge(char **dest, char *src);
/*************************	String replace *********************************/
char			**str_replace(char *str_ori, char **env);

//dollar_handler
char			**dollar_handler(char *str_ori, char **env);
char			*dollar_handler2(char *str, char *ret, char **env);
char			*dollar_handler3(char *str, char *ret, char **env, int *i);
char			*dollar_siquo(char *str, char *ret, int *i);
char			*dollar_doquo(char *str, char *ret, char **env, int *i);

//dollar_expand2
char			*dollar_doquo2(char *str, char *ret, char **env, int *i);
int				after_1_dollar(char *str);
char			*f_add(char *ori, char *to_add, int n);

//dollar_expand3
char			*dollar_out(char *str, char *ret, char **env, int *i);
char			*dollar_in(char *str, char **env, int *i);
char			*dollar_replace(char *str, char **env, int *i);
char			*make_dollar_sign(void);
char			*dollar_replace2(char *str, int *i, int *cnt);
//ft_split_after_dollar_expansion.c
char			**ft_split_after_dollar_expansion(char *str);

//ft_del_quote.c
char			**ft_del_quo(char **str2);
char			*ft_del_quo2(char *str2_i, char *ret);

//wildcard_expand.c
char			**wildcard_expand(char *str, int nbr);

//wildcard_expand2.c
char			**merge_with_wildcard(char **str2, int nbr);

/*************************	Input breaking *********************************/


#endif