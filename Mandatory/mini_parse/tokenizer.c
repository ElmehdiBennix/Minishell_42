/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:18:41 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/14 05:19:36 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// t_lex *tokenizer(t_token *tokens)
// {
//     t_token *head = tokens;

//     while(head)
//     {
        

//     }
// }

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