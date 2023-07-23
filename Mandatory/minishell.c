/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:17:11 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/23 04:14:23 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"


void get_fstr()
{
    char *content;

    while (1)
    {
        content= readline("Mininshell :");
        // printf("%s\n", content);
        content = ft_strtrim(content, " ");
        tokeni(content);
    }
}

int main()
{
    extern char **env;
    get_fstr();
}