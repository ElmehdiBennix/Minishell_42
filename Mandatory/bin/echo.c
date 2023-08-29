/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:03 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/03 12:01:18 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_option(char **av)
{
	int	i;
	int j;
	int	flg;
	
	flg = 0;
	i = 1;
	while (av[i])
	{
		if (!ft_strncmp(av[i], "-n", 2))
		{
			j = 1;
			while(av[i][j] && av[i][j] == 'n')
				j++;
			if (!av[i][j])
				flg += 1;
			else
				return (flg);
		}
		i++;
	}
	return (flg);
}
// i still need to handel the option case

void	my_echo(char **av, t_env *env)
{
	int	i;
	int	option;
	int flag;

	(void)env;
	i = 1;
	option = check_option(av);
	if (option != 0)
		i += option;
	flag = 1;
	while (av[i])
	{
		if (!flag)
			write(1, " ", 1);
		ft_putstr_fd(av[i], 1);// file descriptor not set yet
		flag = 0;
		// write(1, " ", 1);// should handle space befor args
		i++;
	}
	if (option == 0)
		printf("\n");
}