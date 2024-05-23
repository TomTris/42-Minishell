/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 04:00:33 by qdo               #+#    #+#             */
/*   Updated: 2024/05/23 09:33:59 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft/libft.h"
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define OR 1
# define AND 2
# define PIPE 3
# define O_PARENT 4
# define C_PARENT 5
# define RE_IN 6
# define RE_OUT 7
# define HERE_DOC 8
# define APPEND 9
# define NL 10

typedef struct s_mini	t_mini;
//sign 0 nothing
//sign 1 = <
//sign 2 = >
//sign 3 = <<
//sign 4 = >>

typedef struct s_redirection
{
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
int				free_split(char **to_free2);
int				free_mini(t_mini *mini);

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
char			*dollar_underscore(char **cmd, int only_return, int free_check);
char			**ft_del_quo(char **str2);
char			*ft_del_quo2(char *str2_i, char *ret);

/*************************  ft_clean *********************************/
//ft_clean1 && 2
int				ft_fd_heredoc(int fd_new);
int				ft_fd_dup(int fd_new);
int				ft_fd_redi_dup(int fd_new);
int				ft_fd_redi_dup(int fd_new);

int				ft_clean_programm(t_mini *mini_outside, int exit_nbr);

/*************************	String replace *********************************/
//expansion_0
char			**str_replace(char *str_ori, char **env);
void			ft_change_star(char *str, int nbr);
//expansion_dollar1
char			**dollar_handler(char *str_ori, char **env, int nbr);
char			*dollar_handler2(char *str, char *ret, char **env);
char			*dollar_handler3(char *str, char *ret, char **env, int *i);
char			*dollar_siquo(char *str, char *ret, int *i);
char			*dollar_doquo(char *str, char *ret, char **env, int *i);
//expansion_dollar2
char			*dollar_out(char *str, char *ret, char **env, int *i);
char			*dollar_in(char *str, char **env, int *i);
char			*dollar_replace(char *str, char **env, int *i);
char			*dollar_replace2(char *str, int *i, int *cnt);
char			*dollar_replace3(char *str, char **env, int *i);
//expansion_dollar3
char			*make_dollar_sign(void);
int				after_1_dollar(char *str);
char			*f_add(char *ori, char *to_add, int n);
char			*dollar_doquo2(char *str, char *ret, char **env, int *i);
//expansion_dollar4
char			**ft_split_after_dollar_expansion(char *str);
//expansion_wildcard1 && expansion_wildcard1
char			**wildcard_expand(char *str, int nbr, int i);
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
//break_input3_herd
int				ft_heredoc_gen(t_mini_unit *mini_unit, char *str, int *i);
char			*rm_dollar_before_quote(char *str, int i, char *ret);
int				ft_fd_heredoc_new(char *limiter);
int				ft_fd_heredoc_new2(char *limiter, int write_end,
					int limiter_len, int cnt);

//break_input4_heredoc
int				get_fd_heredoc_ori(int fd);
int				ft_cnt_line_heredoc(void);
int				ft_reach_end_of_file(char *limiter, int i);
int				ft_fd_heredoc_add(t_mini_unit *mini_unit, int fd_new_to_add);

//break_input5_heredoc.c
int				ft_512(char *temp);
int				ft_init_helper(int *fd_heredoc_ori, int *len);
//break_input6_redi
int				ft_redi_gen(t_mini_unit *mini_unit,
					char *str, int *i, int type);
int				ft_mini_redi_init(t_mini_unit *mini_unit, char *ret, int type);
int				ft_mini_redi_init2(t_mini_unit *mini_unit,
					t_redirection *mini_redi, char *ret, int type);
t_redirection	*mini_redi_init(t_mini_unit *mini_unit, char *str, int type_re);
char			*mini_redi_get_ret(char **temp);

//execute mini_unit
int				ft_recursion_muni_unit_create(
					pid_t *pid_arr, t_mini_unit *mini_unit, int fd_in);
int				ft_execute_mini_unit(
					t_mini_unit *mini_unit, int fd_in, int fd_out);
int				ft_is_builtin(t_mini_unit *mini_unit);
int				ft_builtin(char **cmd, char ***env_o);
//execute mini.c
int				ft_execute_mini(t_mini *mini);
int				ft_execute_mini2(t_mini *mini, int i, int j);
//execute_sub_mini.c
int				ft_execute_sub_mini(t_sub_mini *sub_mini);
int				ft_execute_sub_mini2(t_sub_mini *sub_mini);
pid_t			*pid_arr_create(int i);
int				ft_wait_pid(pid_t *pid, int nbr);
void			ft_sig_ter(pid_t *pid, int nbr);
//execute_mini_unit_redi
int				ft_redi_execute(t_mini_unit *mini_unit);
int				ft_redi_execute_redi(t_redirection *redi, char **env);
int				ft_redi_execute_heredoc(t_mini_unit *mini_unit);
//execute mini_unit_ft_execve
int				ft_execve(t_mini_unit *mini_unit, int fd_close);
char			**ft_path_gen(char **env);
int				ft_execve_absolut(
					char *cmd, char **args, char **path, char **env);
char			**ft_args_gen(t_mini_unit *mini_unit, char *cmd, int fd_close);
int				ft_fd_out(int fd_new);
//execute mini_unit_ft_execve2
int				ft_execve_absolut(char *cmd, char **args,
					char **path, char **env);
int				ft_execve_dot0(void);

//builtins
int				exit_code(int new);
int				ft_export(char ***env_o, char **cmd);
int				ft_unset(char ***env_o, char **cmd);
int				ft_env(char ***env_o, char *rule, int unset_export);
char			**make_env(char **env);
int				ft_exportpp(char ***env_o, char **cmd, int i);
int				ft_is_exportpp(char **cmd, int i);
int				ft_echo(char **cmd);
int				ft_pwd(void);
int				ft_exit(char **cmd);
int				ft_builtin_env(char **env);
int				ft_cd(char **cmd, char ***env);
int				ft_cd_oldpwd(char ***env);
int				ft_cd_home(char	***env);
int				ft_cd_relativ(char **cmd, char ***env);
int				ft_cd_absolut(char *path, char **cmd, char ***env);
int				ft_pre_set(char **cwd, char **fu_cwd, char *path);

//env after command - execute_sub_mini_helper.c
int				env_underscore2(char *cmd, char **path, char ***env_o);
int				env_underscore3(char ***env_o, char *cmd);
int				env_underscore(char **cmd, char ***env_o);

//execute_mini_unit_ft_execve_gen
char			**ft_path_gen(char **env);
char			**ft_args_gen(t_mini_unit *mini_unit, char *cmd, int fd_close);

void			sigint_handler1(int sig);
void			ft_sig_2(int sig);
void			ft_sig_3(int sig);
void			sigint_handler2(int sig);
void			sigint_handler1(int sig);
void			sigint_handler3(int sig);

#endif