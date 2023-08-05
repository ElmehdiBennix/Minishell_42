/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:06:42 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/05 02:35:04 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*arrow;

	arrow = lst;
	if (arrow)
		while (arrow ->next != NULL)
			arrow = arrow -> next;
	return (arrow);
}
