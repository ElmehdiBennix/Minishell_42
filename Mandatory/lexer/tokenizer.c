/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/25 04:21:19 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// t_token *space_handler(t_token *token, char *line_bef, int len)
// {


// }

t_token   *char_handler(char *prompt, int *i)
{
    // char *word = NULL;
    int moves;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)malloc(sizeof(token));
    while(ft_isalpha(prompt[*i]) == 1) // need to change it to smthing else its for tst now
    {
        (*i)++;
        moves++;
    }
    printf("%d\n",moves);
    token->content = ft_calloc(moves + 1, sizeof(char));
    ft_strlcpy(token->content,prompt,moves + 1);
    printf("%s\n",token->content);
    printf("|||||%c|||||",prompt[*i]);
    if (prompt[*i] == ' ')
        token->space_after = 1;
    else
        token->space_after = 0;
    printf("%d\n",token->space_after);
}


void tokenizer(char *prompt)
{
    int     i;
    t_token *tokens = NULL;
    
    i = 0;
    while (prompt[i])
    {
        // if (prompt[i] ==  ' ')
        //     // tokens = space_handler(token, prompt, i);
        // else if(prompt[i] == '|')
        //     // tokens = separateur_handler();
        // else
            char_handler(prompt, &i);
        tokens = tokens->forward;   
        i++;
    }
}