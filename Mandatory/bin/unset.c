/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:35 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/01 13:11:05 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_unset(char *option, char *val, t_env *env)
{
	if (option)
	{
		if (!ft_strcmp(option, "-v"))
	}
	ft_remove_node(&env, val, ft_strcmp);
	while(env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}