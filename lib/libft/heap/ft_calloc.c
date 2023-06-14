/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 22:10:49 by ebennix           #+#    #+#             */
/*   Updated: 2023/04/20 02:41:41 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

void	*ft_calloc(size_t nelem, size_t size)
{
	void	*p;

	p = (char *)malloc ((nelem * size) * sizeof(char));
	if (!p)
		return (0);
	ft_bzero(p, (nelem * size));
	return (p);
}
