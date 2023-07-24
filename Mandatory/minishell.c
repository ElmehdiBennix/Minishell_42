/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:17:11 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/24 00:06:09 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

// "nobody told you that the journey gonna be that easy" --> stop thiniking -> start acting ??  
void get_fstr()
{
    char *content;

    while (1)
    {
        content= readline("Mininshell :");
        // printf("%s\n", content);
        content = ft_strtrim(content, " ");
        valid_cmd(content);
        // tokeni(content);
    }
}

int main()
{
    extern char **env;
    get_fstr();
}