/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:05:35 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/22 03:24:51 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
#include <readline/readline.h>

void minishell()
{
    char *content;

    while(1)
    {
        content = readline("le minishit : "); // should display corrent dir and exit msgs zith colors
        ft_fprintf(1,"%s\n",content);
    }
}=

int main()
{
    extern char **environ;
    minishell();

}
