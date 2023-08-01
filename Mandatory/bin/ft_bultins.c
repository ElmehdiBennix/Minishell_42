/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bultins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:50:58 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/01 14:43:10 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_bultin(char **arg, t_env *env)
{
		
	if (ft_strcmp(arg[1], "env") == 0)
		ft_env(env);
	else if (ft_strcmp(arg[1], "unset") == 0)
		ft_unset(arg[2], arg[3], env);
}