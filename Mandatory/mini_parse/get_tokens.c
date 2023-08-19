/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/19 14:07:38 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_type get_type(char *token , int moves) // flag true for string false for char
{
    if (moves == 1)
    {
        if(*token == '|')
            return PIPE;
        else if(*token == '>')
            return GREAT;
        else if(*token == '<')
            return LESS;
    }
    else
    {
        if (ft_strncmp(token,">>",2) == 0)
            return GREAT_GREAT;
        if (ft_strncmp(token,"<<",2) == 0)
            return LESS_LESS;
        else if (ft_strncmp(token,"><",2) == 0 || strncmp(token,"<|",2) == 0)
            return -1;
        else
            return PIPE_RED; // need to ask around about this // should be splet up thqts the key
    }
    return (0); // needs a better logic
}

t_token   *char_handler(char *prompt, int *i)
{
    int moves;
    int backward;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)ft_calloc(sizeof(t_token),1);
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
    token->type = WORD;
    if (prompt[*i] == ' ')
        token->space_after = 1;
    else
        token->space_after = 0;
    printf("%d type = %d  \n",token->space_after,token->type);
    return (token);
}

// missing prots

t_token   *QUOT_handler(char *prompt, int *i , char QUOT_type)
{
    int moves;
    int backward;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)ft_calloc(sizeof(t_token),1); // move down
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
    if (QUOT_type == 39)
        token->type = SINGLE_QUOT;
    else
        token->type = DOUBLE_QUOT;
    printf("%d type = %d  \n",token->space_after,token->type);
    return (token);
}

t_token   *separateur_handler(char *prompt, int *i) // << >> |>  <|
{
    int moves;
    int backward = 0;
    t_token *token = NULL;
    
    moves = 0; //><
    token = (t_token *)ft_calloc(sizeof(t_token),1);
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
        exit_msg(2,"parse error",RED , 52); //free data
    printf("%d\n",moves);
    token->content = ft_calloc(moves + 1, sizeof(char));
    backward = (*i) - moves;
    ft_strlcpy(token->content,&prompt[backward],moves + 1);
    printf("%s\n",token->content);
    printf("|||||%c|||||",prompt[*i]);
    int x = get_type(token->content,moves);
    if (x == -1)
        exit_msg(2,"parse error",RED , 52); //free data and return set errno to error number
    token->type = x;
    if (prompt[*i] == ' ')
        token->space_after = 1;
    else
        token->space_after = 0;
    printf("%d type = %d  \n",token->space_after,token->type);
    return (token);
}


t_token *get_tokens(char *prompt)
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