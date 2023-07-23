/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:26:26 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/23 02:17:38 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int echo(char *string, bool flag)
{
    if (flag == 0)
        ft_fprintf(1,"%s\n",string);
    else
        ft_fprintf(1,"%s",string);
    return (0);
}