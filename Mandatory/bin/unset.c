/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:35 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/28 02:22:22 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_unset(char **arg, t_env **env)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		ft_remove_node(env, arg[i], ft_strcmp);
		i++;
	}
}
