/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:27:10 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/22 06:21:15 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

void	ft_lstfree(void *stack)
{
	t_list	*arrow;

	arrow = stack;
	while (arrow)
	{		
		free(arrow);
		arrow = arrow -> next;
	}
}
