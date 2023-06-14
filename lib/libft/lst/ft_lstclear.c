/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 02:13:53 by ebennix           #+#    #+#             */
/*   Updated: 2023/04/27 10:22:22 by ebennix          ###   ########.fr       */
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
