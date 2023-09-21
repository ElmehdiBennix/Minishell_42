/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:03 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/21 05:35:01 by ebennix          ###   ########.fr       */
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

void	my_echo(char **cmd_array)
{
	int	i;
	int	option;
	int flag;

	i = 1;
	option = check_option(cmd_array);
	if (option != 0)
		i += option;
	flag = 1;
	while (cmd_array[i])
	{
		if (!flag)
			write(1, " ", 1);
		ft_putstr_fd(cmd_array[i], 1);		
		flag = 0;
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
}
//all fixed
