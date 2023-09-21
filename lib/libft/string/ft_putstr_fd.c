/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 01:07:37 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/21 05:42:50 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

#if !defined(libss)
#define libss

#include <stdio.h>

#endif // libss


void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
