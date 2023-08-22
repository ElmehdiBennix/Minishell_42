/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:18 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/05 19:45:42 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

void	check_valid_args(char **ag, int *ex, int *index)
{
	int i;
	int c;

	i = 0;
	c = 1;
	if (ag[1][0] == '-' || ag[1][0] == '+')
		i++;
	while(ag[c])
		c++;
	while (ag[1][i])
	{
		if (ag[1][i] >= '0' && ag[1][i] <= '9')
			i++;
		else
		{
			printf("problem encountered\n");
			// free_env();
			exit (255);
		}
	}
	if (c > 2)
	{
		*ex = 1;
		*index = -1;
		printf("too many args\n");
	}
}
int	mini_exit(char **av, t_env *env, int exit_status)
{
	int		i;

	(void)env;
	i = 0;
	if (!av[1])
		exit(exit_status);
	else
		check_valid_args(av, &exit_status, &i);
	if (i < 0)
		return (exit_status);
	// free_env();//
	exit(ft_atoi(av[1]));
}
