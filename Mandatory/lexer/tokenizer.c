/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/25 05:37:25 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token   *char_handler(char *prompt, int *i)
{
    int moves;
    int backward;
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
    backward = (*i) - moves;
    ft_strlcpy(token->content,&prompt[backward],moves + 1);
    printf("%s\n",token->content);
    printf("|||||%c|||||",prompt[*i]);
    if (prompt[*i] == ' ')
        token->space_after = 1;
    else
        token->space_after = 0;
    printf("%d\n",token->space_after);
    token->forward = NULL;
    token->backward = NULL;
    return (token);
}
t_token   *doubleQUOT_handler(char *prompt, int *i)
{
    int moves;
    int backward;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)malloc(sizeof(token));
    while (prompt[*i] == 34 || prompt[*i] == 39)
    {
        (*i)++;
        moves++;
    }
    printf("%d\n",moves);
    token->content = ft_calloc(moves + 1, sizeof(char));
    backward = (*i) - moves;
    ft_strlcpy(token->content,&prompt[backward],moves + 1);
    printf("%s\n",token->content);
    printf("|||||%c|||||",prompt[*i]);
    if (prompt[*i] == ' ')
        token->space_after = 1;
    else
        token->space_after = 0;
    printf("%d\n",token->space_after);
    token->forward = NULL;
    token->backward = NULL;
    return (token);
}

void tokenizer(char *prompt)
{
    int     i;
    t_token *tokens = NULL;
    
    i = 0;
    while (prompt[i])
    {
        if (prompt[i] == ' ')
            i++;
        // else if (prompt[i] == '|')
        //     tokens = separateur_handler();
        else if (prompt[i] == 34) // double quot
        {
            tokens = doubleQUOT_handler(prompt, &i);
            tokens = tokens->forward;
        }
        // else if (prompt[i] == 39) // single qout
        // {
        //     tokens = doubleQUOT_handler(prompt, &i);
        //     tokens = tokens->forward;
        // }
        else
        {
            tokens = char_handler(prompt, &i);
            tokens = tokens->forward;
        }
    }
    // need to lego it with the backward node
}