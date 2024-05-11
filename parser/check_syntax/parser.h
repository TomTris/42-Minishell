/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:38:47 by qdo               #+#    #+#             */
/*   Updated: 2024/05/11 00:02:07 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../libft/libft.h"

# define OR_SIGN 1
# define AND_SIGN 2
# define PIPE_SIGN 3

// nothing		0;
// or_sign		1
// and_sign		2
// pipe_sign	3;
typedef struct s_input_break
{
	int		nbr;
	int		in_fd;
	int		out_fd;
	int		sign_before;
	int		sign_after;
	char	*str;
}	t_input_break;



int		ft_parenthesis_close_find(char *str);
int		ft_check_syntax(char *str);

/***************************check_syntax *************************/
int		ft_pre_check_input(char *str);

int		ft_find_sign_before(char *str, int i);
int		ft_find_sign_after(char *str, int i);
int		ft_parenthesis_check_uniq(char *str);

int		ft_count_valid_characters_of_a_word(char *str);
int		ft_skip_redirection(char *str);
int		ft_print_str_error(char *str, int i);

int		ft_sign_check_empty(char *str);


#endif
