/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2023/06/14 21:05:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/23 04:26:56 by ebennix          ###   ########.fr       */
=======
/*   Created: 2023/07/22 23:17:11 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/23 04:14:23 by otaraki          ###   ########.fr       */
>>>>>>> e2d0acbf17adddfb21e38f42efc73376f5d42a49
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"


void get_fstr()
{
    char *content;

    while (1)
    {
<<<<<<< HEAD
        prompt = readline("le minishit : "); // should display corrent dir and exit msgs zith colors
        // ft_fprintf(1,"%s\n",prompt);
        // parsing(prompt);
        // this is it le 
=======
        content= readline("Mininshell :");
        // printf("%s\n", content);
        content = ft_strtrim(content, " ");
        tokeni(content);
>>>>>>> e2d0acbf17adddfb21e38f42efc73376f5d42a49
    }
}

int main()
{
    extern char **env;
    get_fstr();
}