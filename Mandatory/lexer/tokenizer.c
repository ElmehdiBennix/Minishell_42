/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/27 03:47:34 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_ischar(char c)
{
    if (c == 33 || (c >= 35 && c <= 38) || (c >= 40 && c <= 59)    // n9der nzgel chi l3ba so recheck this depends 
        || (c >=  63 && c <= 126 ) || c == 61)
        return (1);
    return (0);
}

int ft_is_separateur(char c)
{
    if (c == 124 || c == 60 || c == 62)
        return (1);
    return (0);
}

t_token   *char_handler(char *prompt, int *i)
{
    int moves;
    int backward;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)malloc(sizeof(token));
    while(ft_ischar(prompt[*i]) == 1) // need to change it to smthing else its for tst now
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

// missing prots

t_token   *QUOT_handler(char *prompt, int *i , char QUOT_type)
{
    int moves;
    int backward;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)malloc(sizeof(token)); // move down
    (*i)++;
    while (prompt[*i] != QUOT_type)
    {
        (*i)++;
        moves++;
    }
    // protectionsssssss
    (*i)++;
    printf("%d\n",moves);
    token->content = ft_calloc(moves + 3, sizeof(char));
    backward = (*i) - moves - 2;
    ft_strlcpy(token->content,&prompt[backward],moves + 3);
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

t_token   *separateur_handler(char *prompt, int *i)
{
    int moves;
    int backward;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)malloc(sizeof(token));
    if (ft_is_separateur(prompt[*i]) == 1) // need to change it to smthing else its for tst now
    {
        (*i)++;
        moves++;
        if (prompt[*i] == '>' || prompt[*i] == '<')
        {
            (*i)++;
            moves++;
        }
    }
    if (moves >= 2)
        exit_msg(2,"paser error",RED , 2);
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
        else if (prompt[i] == '|' || prompt[i] == '<' || prompt[i] == '>')
        {
            tokens = separateur_handler(prompt, &i);
            tokens = tokens->forward;
        }
        else if (prompt[i] == 34) // double quot
        {
            tokens = QUOT_handler(prompt, &i , 34);
            tokens = tokens->forward;
        }
        else if (prompt[i] == 39) // single qout
        {
            tokens = QUOT_handler(prompt, &i , 39);
            tokens = tokens->forward;
        }
        else
        {
            tokens = char_handler(prompt, &i);
            tokens = tokens->forward;
        }
    }
    // need to lego it with the backward node
}
