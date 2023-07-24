/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:47:54 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/24 01:08:38 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    check_after_pipe(char *line, int index)
{
    if (ft_isalnum(line[index + 1]))
        printf("is allright");
    else if (ft_isalnum(line[index - 1]))
        printf("is allright");
}

void    valid_cmd(char *cmd)
{
   int  i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '|')
            check_after_pipe();
        if (cmd[i] == '<')
            check_after_rri();
        if (cmd[i] == '>')
            check_after_rli();
        
        i++;
    }
}
