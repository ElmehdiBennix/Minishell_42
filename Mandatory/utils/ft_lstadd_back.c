/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:06:46 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/29 23:08:00 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env *ft_lstlast_env(t_env *node)
{
	if (!node)
		return NULL;
	if (node->next == NULL)
		return node;
	while (node->next)
	{
		node = node->next;
	}
	return node;
}
// void	ft_lstadd_back_env(t_env **lst, t_env *new) // useless already in libft
// {
// 	t_env	*arrow;

// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		arrow = ft_lstlast_env(*lst);
// 		arrow -> next = new;
// 	}
// }
