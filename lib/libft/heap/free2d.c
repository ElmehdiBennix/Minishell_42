/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:11:15 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/21 03:30:14 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

char	**free2d(char **str)
{
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
	return (str);
}
