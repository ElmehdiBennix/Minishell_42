/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:18:41 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/20 20:13:12 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void    split_token(t_token *tokens) // >| cases |< cases |> cases // there is problems still regarding the free realocation of the string
// {
//     t_token *spl_token;
//     char *red_pipe = ft_strdup(tokens->content); // higher complexity more leaks tooo 
    
//     spl_token = (t_token *)ft_calloc(sizeof(t_token),1);
//     spl_token->id = tokens->id + 1;
//     spl_token->space_after = tokens->space_after;
//     tokens->space_after = 0;
//     spl_token->content = ft_calloc(2,1);
//     spl_token->content[0] = red_pipe[1];
//     spl_token->type = get_type(spl_token->content ,1);
//     free(tokens->content);
//     tokens->content = ft_calloc(2,1);
//     tokens->content[0] = red_pipe[0];
//     tokens->type = get_type(tokens->content ,1);
//     t_token *tmp = tokens->forward;
//     tokens->forward = spl_token;
//     spl_token->backward = tokens;
//     spl_token->forward = tmp;
// }
// token can pass the limite of 3 if its a |>>

int	tokens_checker(t_token *token)
{
	if ((token->type == PIPE && token->forward->type == PIPE)
		|| (token->type == GREAT && token->forward->type == GREAT)
		|| (token->type == GREAT && token->forward->type == LESS)
		|| (token->type == GREAT && token->forward->type == APPEND)
		|| (token->type == GREAT && token->forward->type == HERE_DOC)
		|| (token->type == LESS && token->forward->type == GREAT)
		|| (token->type == LESS && token->forward->type == LESS)
		|| (token->type == LESS && token->forward->type == APPEND)
		|| (token->type == LESS && token->forward->type == HERE_DOC)
		|| (token->type == LESS && token->forward->type == PIPE)
		|| (token->type == HERE_DOC && token->forward->type == GREAT)
		|| (token->type == HERE_DOC && token->forward->type == LESS)
		|| (token->type == HERE_DOC && token->forward->type == APPEND)
		|| (token->type == HERE_DOC && token->forward->type == HERE_DOC)
		|| (token->type == HERE_DOC && token->forward->type == PIPE)
		|| (token->type == APPEND && token->forward->type == GREAT)
		|| (token->type == APPEND && token->forward->type == LESS)
		|| (token->type == APPEND && token->forward->type == APPEND)
		|| (token->type == APPEND && token->forward->type == HERE_DOC)
		|| (token->type == APPEND && token->forward->type == PIPE)
	)
    {
        ft_fprintf(2,"le minishell: syntax error near unexpected token `%s'\n",token->forward->content);
		return (1);
    }
	return (0);
}

void tokenizer(t_token *tokens)
{
    t_token *arrow = tokens;
    int i = 0;
    int token_number = 0;

    while(arrow->forward)
    {
        arrow->id = i;
        printf("%s\n",arrow->content);
        if (arrow->type >= PIPE && arrow->type <= HERE_DOC) // need a smarter implementation
        {
            tokens_checker(arrow); // check how many tokens in repeat till it fails 
            token_number++;
        }
        else if (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT)
            token_number = 0;
        // if (arrow->type == PIPE_RED)
        // {   
        //    split_token(arrow);
        //    i++;
        // }
        i++;
        arrow = arrow->forward;
    }
    printf("token counter %d \n",token_number); // shoudnt pass -> le minishit$ ls > | cat this should ls >| cat

    // while(tokens)
    // {
    //     printf("%s    de_type %d\n",tokens->content,tokens->type);
    //     tokens = tokens->forward;
    // }
}



// bennix@MehdiPC:~/myProjects/Minishell_42$ echo > >< ls
// bash: syntax error near unexpected token `>

// parse errors now if else if ellse for tokens then make 2d array to pipes
/*if double qoute trim them and then join with ... */

