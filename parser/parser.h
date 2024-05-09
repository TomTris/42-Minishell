/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:38:47 by qdo               #+#    #+#             */
/*   Updated: 2024/05/09 13:59:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
# include "../libft/libft.h"

typedef struct s_groups_break
{
	char	or_sign[3];
	char	and_sign[3];
	char	doublequote[2];
	char	singlequote[2];
	char	parenthesis_open[2];
	char	parenthesis_close[2];
	char	pipe_sign[2];
}	t_groups_break;

# define DOUBLEQUOTE 1
# define SINGLEQUOTE 2
# define OR_SIGN 3
# define AND_SIGN 4
# define PIPE_SIGN 5
# define PARENTHESIS_OPEN 6
# define PATHENTHESIS_CLOSE 7

// nothing		0;
// doublequote	1
// singlequote	2
// or_sign		3
// and_sign		4
// pipe_sign	5;
// parenthesis_open		6;
// parenthesis_close	7;
typedef struct s_input_break
{
	int		nbr;
	int		in_fd;
	int		out_fd;
	int		sign_before;
	int		sign_after;
	char	*str;
}	t_input_break;


int		ft_pre_check_input(char *str);

int		ft_parenthesis_close_find(char *str);
char	*ft_trim_whitespace(char *str);

#endif
