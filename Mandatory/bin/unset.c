/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:35 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/21 04:31:01 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_unset(char **arg, t_env *env)
{
	int i;

	i = 1;
	// //// check for invalid arguments//////////
	while(arg[i])
	{
		ft_remove_node(&env, arg[i], ft_strcmp);
		i++;
	}
	// while(env)
    // {
    //     printf("%s=%s\n", env->key, env->value);
    //     env = env->next;
    // }
}