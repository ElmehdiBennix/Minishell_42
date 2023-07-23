/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:26:31 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/22 23:55:59 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int exit_bin(int exit_num)
{
    // free all data allocated then exit with exit_num
    exit(exit_num);
}
int main (int ac, char **av)
{
    (void)ac;
    exit_bin(atoi(av[1]));
}

