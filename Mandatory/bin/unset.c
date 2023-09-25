/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:35 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/25 03:13:40 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int					ft_lstsize_env(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void ft_unset(char **arg, t_env **env)
{
	int i;

	i = 1;

	while(arg[i])
	{
		printf("%s == %d\n",arg[i],i);
		ft_remove_node(env, arg[i], ft_strcmp);
		i++;
	}
	printf("%p == env\n",env);
	// if (flg == (i))
	// 	env = NULL;
	// while(env)
    // {
    //     printf("%s=%s\n", env->key, env->value);
    //     env = env->next;
    // }
}