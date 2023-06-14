/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:45:39 by ebennix           #+#    #+#             */
/*   Updated: 2023/04/20 02:38:40 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.h"

static int	check(int fd, const char str, va_list arg)
{
	if (str == 'c')
		return (ft_printchar(fd, va_arg(arg, int)));
	else if (str == 's')
		return (ft_printstr(fd, va_arg(arg, char *)));
	else if (str == 'p')
	{
		write(1, "0x", 2);
		return (ft_hex(fd, va_arg(arg, unsigned long), 'x') + 2);
	}
	else if (str == 'i' || str == 'd')
		return (ft_printnbr(fd, va_arg(arg, int)));
	else if (str == 'u')
		return (ft_printunsigned(fd, va_arg(arg, unsigned int)));
	else if (str == 'x' || str == 'X')
		return (ft_hex(fd, va_arg(arg, unsigned int), str));
	else if (str == '%')
		return (ft_printchar(fd, '%'));
	else
		return (ft_printchar(fd, str));
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	arg;
	int		i;
	int		value;

	i = 0;
	value = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			value += check(fd, str[i], arg);
		}
		else
			value += write(fd, &str[i], 1);
		i++;
	}
	va_end(arg);
	return (value);
}
