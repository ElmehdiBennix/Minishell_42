/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:11:15 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/21 07:08:41 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

char	**free2d(char **array)
{
	int		i;

	i = -1;
	if (!array)
		return (NULL);
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	array = NULL;
	return (array);
}
