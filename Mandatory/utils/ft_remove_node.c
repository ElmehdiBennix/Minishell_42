/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:25:30 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/06 19:34:46 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_remove_node(t_env **env, void *arg, int (*cmp)())
{
	t_env	*current;

	if (env == NULL || *env == NULL)
		return ;
	current = *env;
	if (cmp(current->key, arg) == 0)
	{
		if (current->next)
		{
			*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
		}
		else
		{
			free(current->key);
			free(current->value);
			free(current);
			*env = NULL;
		}
		ft_remove_node(env, arg, cmp);
	}
	current = *env;
	if (current)
		ft_remove_node(&current->next, arg, cmp);
}
