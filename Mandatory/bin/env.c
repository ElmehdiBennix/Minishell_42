/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:26:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/23 00:53:05 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int enva(char **vars)
{
    while(*vars)
    {
        printf("%s\n",*vars);
        vars++;
    }
    return(1);

}
int main (int ac ,char **av ,char **env)
{
    enva(env);

}