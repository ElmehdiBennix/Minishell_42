/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:51:42 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/28 17:34:55 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

int	ft_hex(int fd, int n, char flag)
{
	int	i;

	i = 0;
	if (n >= 0 && n <= 9)
		i += ft_printchar(fd, n + '0');
	else if (n >= 10 && n <= 15)
	{
		if (flag == 'x')
			i += ft_printchar(fd, n + 'W');
		else
			i += ft_printchar(fd, n + '7');
	}
	else
	{
		i += ft_hex(fd, n / 16, flag);
		i += ft_hex(fd, n % 16, flag);
	}
	return (i);
}
