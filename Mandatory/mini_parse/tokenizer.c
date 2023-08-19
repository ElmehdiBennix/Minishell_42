/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:18:41 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/19 14:51:30 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    split_token(t_token *tokens) // >| cases |< cases |> cases // there is problems still regarding the free realocation of the string
{
    t_token *spl_token;
    char *red_pipe = ft_strdup(tokens->content); // higher complexity more leaks tooo 
    
    spl_token = (t_token *)ft_calloc(sizeof(t_token),1);
    spl_token->id = tokens->id + 1;
    spl_token->space_after = tokens->space_after;
    tokens->space_after = 0;
    spl_token->content = ft_calloc(2,1);
    spl_token->content[0] = red_pipe[1];
    spl_token->type = get_type(spl_token->content ,1);
    free(tokens->content);
    tokens->content = ft_calloc(2,1);
    tokens->content[0] = red_pipe[0];
    tokens->type = get_type(tokens->content ,1);
    t_token *tmp = tokens->forward;
    tokens->forward = spl_token;
    spl_token->backward = tokens;
    spl_token->forward = tmp;
}


void tokenizer(t_token *tokens)
{
    t_token *arrow = tokens;
    int i = 0;

    while(arrow->forward)
    {
        arrow->id = i;
        if (arrow->type == PIPE_RED)
        {   
           split_token(arrow);
           i++;
        }
        i++;
        arrow = arrow->forward;
    }

    while(tokens)
    {
        printf("%s    de_type %d\n",tokens->content,tokens->type);
        tokens = tokens->forward;
    }
}

// parse errors now if else if ellse for tokens then make 2d array to pipes
/*if double qoute trim them and then join with ... */

// int	token_checker(t_token *token)
// {
// 	if ((token->type == PIPE && token->forward && token->forward->type == PIPE)
// 		|| (token->type == GREAT && token->forward && token->forward->type == GREAT)
// 		|| (token->type == GREAT && token->forward && token->forward->type == LESS)
// 		|| (token->type == GREAT && token->forward && token->forward->type == APPEND)
// 		|| (token->type == GREAT && token->forward && token->forward->type == HERE_DOC)
// 		|| (token->type == GREAT && token->forward && token->forward->type == PIPE)
// 		|| (token->type == LESS && token->forward && token->forward->type == GREAT)
// 		|| (token->type == LESS && token->forward && token->forward->type == LESS)
// 		|| (token->type == LESS && token->forward && token->forward->type == APPEND)
// 		|| (token->type == LESS && token->forward && token->forward->type == HERE_DOC)
// 		|| (token->type == LESS && token->forward && token->forward->type == PIPE)
// 		|| (token->type == HERE_DOC && token->forward && token->forward->type == GREAT)
// 		|| (token->type == HERE_DOC && token->forward && token->forward->type == LESS)
// 		|| (token->type == HERE_DOC && token->forward && token->forward->type == APPEND)
// 		|| (token->type == HERE_DOC && token->forward
// 			&& token->forward->type == HERE_DOC)
// 		|| (token->type == HERE_DOC && token->forward && token->forward->type == PIPE)
// 		|| (token->type == APPEND && token->forward && token->forward->type == GREAT)
// 		|| (token->type == APPEND && token->forward && token->forward->type == LESS)
// 		|| (token->type == APPEND && token->forward && token->forward->type == APPEND)
// 		|| (token->type == APPEND && token->forward && token->forward->type == HERE_DOC)
// 		|| (token->type == APPEND && token->forward && token->forward->type == PIPE)
// 	)
// 		return (0);
// 	return (1);
// }