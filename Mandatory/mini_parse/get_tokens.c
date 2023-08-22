/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/22 22:56:57 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token   *char_handler(char *prompt, int *i)
{
    int moves;
    int backward;
    t_token *token = NULL;
    
    moves = 0;
    token = (t_token *)ft_calloc(sizeof(t_token),1);
    while(prompt[*i] && ft_iswhite_space(prompt[*i]) == 0 && ft_iseparateur(prompt[*i]) == 0)
    {
        (*i)++;
        moves++;
    }
    backward = (*i) - moves;
    token->content = ft_calloc(moves + 1, sizeof(char));
    ft_strlcpy(token->content,&prompt[backward],moves + 1);
    token->type = WORD;
    if (prompt[*i] == ' ')
        token->space_after = 1;
    else
        token->space_after = 0;
    return (token); 
}

static t_token   *QUOT_handler(char *prompt, int *i , char QUOT_type)
{
    int moves;
    int backward;
    t_token *token;
    
    moves = 0;
    token = (t_token *)ft_calloc(sizeof(t_token),1);
    (*i)++;
    while (prompt[*i] != QUOT_type)
    {
        (*i)++;
        moves++;
    }
    (*i)++;
    backward = (*i) - moves - 2;
    token->content = ft_calloc(moves + 3, sizeof(char));
    ft_strlcpy(token->content,&prompt[backward],moves + 3);
    if (prompt[*i] == ' ')
        token->space_after = 1;
    else
        token->space_after = 0;
    if (QUOT_type == 39)
        token->type = SINGLE_QUOT;
    else
        token->type = DOUBLE_QUOT;
    return (token);
}

static t_token   *separateur_handler(char *prompt, int *i)
{
    int moves;
    int backward;
    t_token *token;
    
    moves = 0;
    token = (t_token *)ft_calloc(sizeof(t_token),1);
    if (prompt[*i] == '|')
    {
        (*i)++;
        moves++;
    }
    else if (prompt[*i] == '>' || prompt[*i] == '<')
    {
        (*i)++;
        moves++;
        if (prompt[*i] && (prompt[*i] == '>' || prompt[*i] == '<'))
        {
            (*i)++;
            moves++;
        }
    }
    backward = (*i) - moves;
    token->content = ft_calloc(moves + 1, sizeof(char));
    ft_strlcpy(token->content,&prompt[backward],moves + 1);
    get_type(token ,moves);
    if (prompt[*i] == ' ')
        token->space_after = 1;
    else
        token->space_after = 0;
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
        else if (prompt[i] == 34 || prompt[i] == 39)
            ft_lstdoubly(&tokens, QUOT_handler(prompt, &i , prompt[i]));
        else
            ft_lstdoubly(&tokens, char_handler(prompt, &i));
    }
    return(tokens);
}
// fix data ttypes for better code too and leaks of course and manage his shit
// leaks left and whole lots of code managements