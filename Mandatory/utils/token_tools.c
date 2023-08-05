/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:21:30 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/05 03:22:06 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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