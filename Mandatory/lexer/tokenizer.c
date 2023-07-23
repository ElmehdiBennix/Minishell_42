/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/23 04:00:28 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void space_handle(t_token *token, char *line_bef, int len)
// {
//     // bisacaly i need to store all the line before the current W_space
//     t_token *current;
//     char *dst;
    
//     current = token;
//     dst = malloc(sizeof(char) * (len + 1));
//     if (current->flag_s == 0)
//     {
//         current->flag_s = 1;
//         ft_strlcpy(dst, line_bef, len + 1);
//         current->content = dst;
//         printf(" {{{%s}}}\n", current->content);
//     }
// }
// void    sp_handle(t_token *token, char *line);
// void    db_quote_handle(t_token *token, char *line);
// void    sg_quote_handle(t_token *token, char *line);
void    char_handle(t_token *token, char *line, int index)
{
    int i;

    i = 0;
    while (i < index)
    {
        token->content[i] = line[i];
        i++;
    }
}


void tokeni(char *f_line)
{
    int     i;
    t_token *token;
    
    token = (t_token *)malloc(sizeof(t_token));
    i = 0;
    while (f_line[i])
    {
        if (f_line[i] ==  ' ')
        {
            // space_handle(token, f_line, i);
        
        }
        else if(f_line[i] == '|' )
        {
            // pipe_line();
            token = token->next;    
        }
        else if(f_line[i] == 34)
        {
            // db_quote();
            printf(" ");
            token = token->next;    
        }
        else if(f_line[i] == 39)
        {
            // sg_handle();
            printf(" ");
            token = token->next;    
        }
        else
        {
            char_handle(token, f_line, i);
            token = token->next;
            // printf("-%c", f_line[i]);    
        }
        i++;
    }
}