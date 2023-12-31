/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:18 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/05 03:57:33 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_valid_args(char **cmd_array, int *ex, int *index)
{
	int	i;
	int	c;

	i = 0;
	c = 1;
	if (cmd_array[1][0] == '-' || cmd_array[1][0] == '+')
		i++;
	while (cmd_array[c])
		c++;
	while (cmd_array[1][i])
	{
		if (cmd_array[1][i] >= '0' && cmd_array[1][i] <= '9')
			i++;
		else
		{
			ft_fprintf(2, "exit: problem encountered\n");
			exit(255);
		}
	}
	if (c > 2)
	{
		*ex = 1;
		*index = -1;
		ft_fprintf(2, "exit: too many args\n");
	}
}

int	mini_exit(char **cmd_array, int exit_status)
{
	int	i;

	i = 0;
	if (!cmd_array[1])
		exit(exit_status);
	else
		check_valid_args(cmd_array, &exit_status, &i);
	if (i < 0)
		return (exit_status);
	exit(ft_atoi(cmd_array[1]));
}
