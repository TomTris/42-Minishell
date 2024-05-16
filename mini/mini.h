/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:00:33 by qdo               #+#    #+#             */
/*   Updated: 2024/05/16 04:27:58 by qdo              ###   ########.fr       */
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

// i use pipe to store heredoc -> limit 512 bytes.
typedef struct s_mini_unit
{
	int				nbr;
	int				nbr_sum;
	int				lvl;
	char			*str;
	char			**cmd;
	t_redirection	*redi;
	int				*fd_heredoc;
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

/*************************  mini *********************************/
t_mini			*mini0(char *str, char ***env, int lvl);
int				sub_mini0(t_mini *mini);;
int				mini_unit0(t_sub_mini *sub_mini);

/*************************Syntax check *********************************/
int				syntax_precheck(char *str);
int				syntax_check(t_mini_unit *mini_unit, char *str);

/*************************ft_free *********************************/
void			free_mini_unit_redi(t_mini_unit *mini_unit);
int				free_split(char **to_free2);
int				free_mini(t_mini *mini);
// int				free_sub_mini(t_sub_mini *sub_mini);
// int				free_mini_unit(t_mini_unit *mini_unit);

/*************************ft_other *********************************/
//ft_other1
int				print_err(char *str);
int				after_1_parent(char *str);
int				after_mlt_parent(char *str);
int				after_quote(char *str);
int				token(char *str);
//ft_other2
char			**smerge(char **dest, char *src);
int				syn_err(char *str, int sign);
//ft_other3
char			**ft_del_quo(char **str2);
char			*ft_del_quo2(char *str2_i, char *ret);

/*************************  ft_clean *********************************/
//ft_clean1
int				ft_fd_heredoc(int fd_new);
int				*ft_fd_add(int *fd, int fd_new);
int				*ft_fd_heredoc_default(int fd_new);
int				ft_clean_programm(t_mini *mini_outside,
					int exit_nbr, int leaks_check);
//ft_clean2
int				ft_init_heredoc(t_mini *mini);
int				get_fd_heredoc_ori(int fd);
int				ft_lvl_cnt(int lvl_outside);
int				ft_cnt_line_heredoc(void);

/*************************	String replace *********************************/
//expansion_0
char			**str_replace(char *str_ori, char **env);
//expansion_dollar1
char			**dollar_handler(char *str_ori, char **env);
char			*dollar_handler2(char *str, char *ret, char **env);
char			*dollar_handler3(char *str, char *ret, char **env, int *i);
char			*dollar_siquo(char *str, char *ret, int *i);
char			*dollar_doquo(char *str, char *ret, char **env, int *i);
//expansion_dollar2
char			*dollar_out(char *str, char *ret, char **env, int *i);
char			*dollar_in(char *str, char **env, int *i);
char			*dollar_replace(char *str, char **env, int *i);
char			*dollar_replace2(char *str, int *i, int *cnt);
char			*make_dollar_sign(void);
//expansion_dollar3
int				after_1_dollar(char *str);
char			*f_add(char *ori, char *to_add, int n);
char			*dollar_doquo2(char *str, char *ret, char **env, int *i);
//expansion_dollar4
char			**ft_split_after_dollar_expansion(char *str);
//expansion_wildcard1 && expansion_wildcard1
char			**wildcard_expand(char *str, int nbr);
char			**merge_with_wildcard(char **str2, int nbr);

/*************************	Input breaking *********************************/

//break_input
int				break_input(t_mini *mini);
int				make_input_mini(t_mini *mini);
int				make_input_sub_mini(t_sub_mini *sub_mini);
int				make_input_mini_unit(t_mini_unit *mini_unit);
int				make_input_mini_unit2(t_mini_unit *mini_unit,
					char *str, int *i);
//break_input2
int				ft_cmd_gen(t_mini_unit *mini_unit, char *str, int *i);
char			**ft_cmd_create(char **cmd, char *str, char **env);
char			**smerge2(char **s1, char **s2);
int				ft_take_string(char *str, int *i);
//break_input3
int				ft_heredoc_gen(t_mini_unit *mini_unit, char *str, int *i);
int				ft_fd_heredoc_new(char *limiter);
int				ft_fd_heredoc_new2(char *limiter, int write_end);
int				ft_reach_end_of_file(char *limiter);
int				ft_here_doc_add(t_mini_unit *mini_unit, int fd_new_to_add);
//break_input4
int				ft_redi_gen(t_mini_unit *mini_unit,
					char *str, int *i, int type);
int				ft_mini_redi_init(t_mini_unit *mini_unit,
					char **temp, int type);
t_redirection	*mini_redi_init(t_mini_unit *mini_unit, char *str, int type_re);
char			*mini_redi_get_ret(char **temp);

#endif