/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:25:30 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/03 20:21:25 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_remove_node(t_env **begin_list, void *data_ref, int (*cmp)())
{
	if (begin_list == NULL || *begin_list == NULL)
		return;

	t_env *cur = *begin_list;

	if (cmp(cur->key, data_ref) == 0)
	{
		if (cur->next)
		{
			*begin_list = cur->next;
			free(cur);
		}
		else
		{
			free(cur);
			*begin_list = NULL;
		}
		ft_remove_node(begin_list, data_ref, cmp);
	}
	cur = *begin_list;
	if (cur)
		ft_remove_node(&cur->next, data_ref, cmp);
}
