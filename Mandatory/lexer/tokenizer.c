/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/24 05:15:10 by ebennix          ###   ########.fr       */
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


void lexer(char *prompt)
{
    int     i;
    t_token *token;
    
    token = (t_token *)malloc(sizeof(t_token));
    i = 0;
    while (prompt[i])
    {
        if (prompt[i] ==  ' ')
        {
            // space_handle(token, prompt, i);
        
        }
        else if(prompt[i] == '|' )
        {
            // pipe_line();
            token = token->next;    
        }
        else if(prompt[i] == 34)
        {
            // db_quote();
            printf(" ");
            token = token->next;    
        }
        else if(prompt[i] == 39)
        {
            // sg_handle();
            printf(" ");
            token = token->next;    
        }
        else
        {
            char_handle(token, prompt, i);
            token = token->next;
            // printf("-%c", prompt[i]);    
        }
        i++;
    }
}