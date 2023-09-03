/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:03 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/03 21:27:25 by otaraki          ###   ########.fr       */
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
//all fixed

void	my_echo(t_token *data, char **av, t_env **env)
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
		ft_putstr_fd(av[i], data->fdout);// file descriptor seted
		flag = 0;// fixed √
		i++;
	}
	if (option == 0)
		printf("\n");
}
