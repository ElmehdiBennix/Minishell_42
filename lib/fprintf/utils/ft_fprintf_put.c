/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:14:29 by ebennix           #+#    #+#             */
/*   Updated: 2023/04/20 02:40:45 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

int	ft_printchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_printstr(int fd, char *c)
{
	int	i;

	i = 0;
	if (c == NULL)
		return (ft_printstr(fd, "(null)"));
	while (c[i])
	{
		write(fd, &c[i], 1);
		i++;
	}
	return (i);
}

int	ft_printunsigned(int fd, unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 0 && n < 10)
	{
		i += ft_printchar(fd, n + '0');
	}
	else
	{
		i += ft_printunsigned(fd, n / 10);
		i += ft_printunsigned(fd, n % 10);
	}
	return (i);
}

int	ft_printnbr(int fd, int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		i += ft_printstr(fd, "-2147483648");
	}
	else if (n >= 0 && n < 10)
	{
		i += ft_printchar(fd, n + '0');
	}
	else
	{
		if (n < 0)
		{
			i += ft_printchar(fd, '-');
			i += ft_printnbr(fd, n * (-1));
		}
		else
		{
			i += ft_printnbr(fd, n / 10);
			i += ft_printnbr(fd, n % 10);
		}
	}
	return (i);
}
