/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:05:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/23 04:26:56 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void minishell()
{
    char *prompt;

    while(1)
    {
        prompt = readline("le minishit : "); // should display corrent dir and exit msgs zith colors
        // ft_fprintf(1,"%s\n",prompt);
        // parsing(prompt);
        // this is it le 
    }
}

int main()
{
    extern char **environ;
    minishell();

}
