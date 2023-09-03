/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:11 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/03 21:36:43 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(int  fd, t_env *env)
{
	while(env)
	{
		if (env->value)
		{
	    	ft_putstr_fd(env->key, fd);
			ft_putchar_fd('=', fd);
	    	ft_putstr_fd(env->value, fd);
			ft_putchar_fd('\n', fd);
		}
	    env = env->next;
	}
	return (0);
}