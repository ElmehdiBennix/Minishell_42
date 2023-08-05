/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/05 03:14:54 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_iseparateur(char c)
{
    if (c == 124 || c == 60 || c == 62)
        return (1);
    return (0);
}

int ft_iswhite_space(char c)
{
    if (c == ' ' || c == '\r' || c == '\n' || c == '\f' || c ==  '\t' || c ==  '\v')
        return (1);
    return (0);
}

t_token   *char_handler(char *prompt, int *i)
{
    int moves;
    int backward;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)malloc(sizeof(t_token));
    while(prompt[*i] && ft_iswhite_space(prompt[*i]) == 0 && ft_iseparateur(prompt[*i]) == 0) // need to change it to smthing else its for tst now
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
    token = (t_token *)malloc(sizeof(t_token)); // move down
    (*i)++;
    while (prompt[*i] && prompt[*i] != QUOT_type)
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
    token = (t_token *)malloc(sizeof(t_token));
    while (prompt[*i] && ft_iseparateur(prompt[*i]) == 1) // need to change it to smthing else its for tst now eather pipe in token or diretions
    {
        (*i)++;
        moves++;
        if (prompt[*i] == '>' || prompt[*i] == '<') // posible an error in some cases needs testing
        {
            (*i)++;
            moves++;
        }
    }
    if (moves > 2) // strn cmp with all syntaxe errors
        exit_msg(2,"parse error",RED , 52);
    printf("%d\n",moves);
    token->content = ft_calloc(moves + 1, sizeof(char));
    backward = (*i) - moves;
    ft_strlcpy(token->content,&prompt[backward],moves + 1);
    if (strncmp(token->content,"||",2) == 0 || strncmp(token->content,"<|",2) == 0)
        exit_msg(2,"parse error near zbi",RED , 52);
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

void    ft_lstdoubly(t_token **head , t_token *node)
{
    t_token* current = *head;

    if (*head == NULL)
        *head = node;
    else if(node == NULL)
        return; // error
    else
    {
        while (current->forward != NULL)
            current = current->forward;
        current->forward = node;
        node->backward = current;
        node->forward = NULL;
    }
}

t_token *tokenizer(char *prompt)
{
    int     i;
    t_token *tokens = NULL;
    
    i = 0;
    while (prompt[i])
    {
        if (ft_iswhite_space(prompt[i]) == 1)
            i++;
        else if (prompt[i] == '|' || prompt[i] == '<' || prompt[i] == '>')
            ft_lstdoubly(&tokens, separateur_handler(prompt, &i));
        else if (prompt[i] == 34 || prompt[i] == 39) // quots
            ft_lstdoubly(&tokens, QUOT_handler(prompt, &i , prompt[i]));
        else
            ft_lstdoubly(&tokens, char_handler(prompt, &i));
    }
    return(tokens);
}
// fix data ttypes for better code too and leaks of course and manage his shit
// leaks left and whole lots of code managements