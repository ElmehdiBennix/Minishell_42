/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:53:31 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/28 02:28:14 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*sort_list(t_env *lst, int (*cmp)(char *, char *))
{
	char	*swap[2];
	t_env	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (((*cmp)(lst->key, lst->next->key)) == 0)
		{
			swap[0] = lst->key;
			swap[1] = lst->value;
			lst->key = lst->next->key;
			lst->value = lst->next->value;
			lst->next->key = swap[0];
			lst->next->value = swap[1];
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}
