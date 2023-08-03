/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:03 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/03 10:53:40 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_option(char **av)
{
	int	i;
	int	flg;
	
	flg = 0;
	i = 1;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-n"))
			flg += 1;
		i++;
	}
	return (flg);
}
// i still need to handel the option case

void	my_echo(char **av, t_env *env)
{
	int	i;
	int	option;

	(void)env;
	i = 1;
	option = check_option(av);
	if (option != 0)
		i += option;
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);// file descriptor not set yet
		write(1, " ", 1);// should handle space befor args
		i++;
	}
	if (option == 0)
		printf("\n");
}
