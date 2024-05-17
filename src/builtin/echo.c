/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:27:44 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/17 18:03:28 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//	echo
//	echo ~ , even if home is unset
//	echo -nnnnn -n -n test
//	echo -nnnnnadsfasdadasdasda -n -n -n test
//	echo -asghhjgjf
int	is_n_flag(char *option)
{
	int	i;

	if (option[0]!='-')
		return (0);
	i = 1;
	while (option[i] == 'n')
		i++;
	if (option[i] != 0)
		return (0);
	else
		return (1);
}

void	print_arg(char *arg)
{
	if (scmp(arg, "~"))
		ft_printf("%s", arg);
	else
		ft_printf("%s", get_env()->home);
}

void	on_echo(t_exec e)
{
	int	i;
	int	skip_nl;

	skip_nl = 0;
	if (e.argc == 1)
		ft_printf("\n");
	else
	{
		i = 1;
		while ((i == 1 || skip_nl) && is_n_flag(e.argv[i]))
		{
			i++;
			skip_nl = 1;
		}
		while (i < e.argc)
		{
			print_arg(e.argv[i++]);
			if (i < e.argc)
				ft_printf(" ");
		}
		if (!skip_nl)
			ft_printf("\n");
	}
	set_exit_code(0);
}
