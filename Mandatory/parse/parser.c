/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:18:41 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 00:20:23 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	forbidden_tokens(t_token *token)
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
	|| (token->type == GREAT && token->space_after == TRUE
		&& token->forward->type == PIPE))
		return (1);
	return(0);
}

bool	tokens_checker(t_token *token, int *nodes)
{
	t_token	*tmp;

	tmp = NULL;
	if (forbidden_tokens(token) == TRUE)
		return(ft_fprintf(2, "le minishell: syntax error near unexpected token `%s'\n", token->forward->content), 1);
	else if ((token->type == GREAT && token->space_after == FALSE
				&& token->forward->type == PIPE))
	{
		tmp = token->forward;
		token->forward->forward->backward = token;
		token->forward = token->forward->forward;
		(*nodes)--;
		free(tmp->content);
		free(tmp);
	}
	return (0);
}

bool	parser(t_mini_data *var)
{
	t_token	*arrow;
	int		token_number;

	arrow = var->tokens;
	token_number = 0;
	while (arrow->forward)
	{
		if ((arrow->type >= PIPE && arrow->type <= HERE_DOC))
		{
			if (tokens_checker(arrow, &var->nodes) == TRUE)
				return (1);
			token_number++;
		}
		else if (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT)
			token_number = 0;
		if (token_number == 3 || arrow->type == 10)
			return (ft_fprintf(2, "le minishell: syntax error near unexpected token `%s'\n", arrow->content), 1);
		arrow = arrow->forward;
	}
	return (0);
}
