/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/24 00:05:48 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void space_handle(t_token *token, char *line_bef, int len)
{
    // bisacaly i need to store all the line before the current W_space
    t_token *current;
    char *dst;
    
    current = token;
    dst = malloc(sizeof(char) * (len + 1));
    if (current->flag_s == 0)
    {
        // current->flag_s = 1;
        ft_strlcpy(dst, line_bef, len + 1);
        current->content = dst;
        printf(" {{{%s}}}\n", current->content);
    }
}
// void    sp_handle(t_token *token, char *line);
// void    db_quote_handle(t_token *token, char *line);
// void    sg_quote_handle(t_token *token, char *line);
// int    char_handle(t_token *token, char *line, int index);

// aim about recursion functions each time you check the next char 


// void tokeni(char *f_line)
// {
    
// }