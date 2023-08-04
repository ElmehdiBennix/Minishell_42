/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:18 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/04 13:49:31 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int	mini_exit(t_env *env, int i)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		tmp = tmp->next;
	}
	printf("%d\n", i);
	return (exit(i), i);
}
