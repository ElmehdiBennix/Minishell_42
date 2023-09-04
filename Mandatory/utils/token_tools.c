/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:21:30 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/03 15:05:13 by ebennix          ###   ########.fr       */
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

void    get_type(t_token *token , int moves)
{
    if (moves == 1)
    {
        if (*token->content == '|')
            token->type = PIPE;
        else if (*token->content == '>')
            token->type = GREAT;
        else if (*token->content == '<')
            token->type = LESS;
    }
    else
    {
        if (ft_strncmp(token->content,">>",2) == 0)
            token->type = APPEND;
        if (ft_strncmp(token->content,"<<",2) == 0)
            token->type = HERE_DOC;
        else
            token->type = 10;
    }
}

void    ft_lstdoubly(t_token **head , t_token *node)
{
    t_token* current = *head;

    if (*head == NULL)
        *head = node;
    else if (node == NULL)
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
