/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:18:41 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/25 00:43:39 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		|| (token->type == GREAT && token->space_after == TRUE
			&& token->forward->type == PIPE))
	{
		ft_fprintf(2, "le minishell: syntax error near unexpected token `%s'\n",
				token->forward->content);
		return (1); // set erno and free repeat loop
	}
	return (0);
}

bool	tokenizer(t_token *tokens)
{
	t_token			*arrow;
	unsigned int	i;
	int				token_number;

	arrow = tokens;
	i = 0;
	token_number = 0;
	while (arrow->forward)
	{
		arrow->id = i;
		if ((arrow->type >= PIPE && arrow->type <= HERE_DOC))
		{
			tokens_checker(arrow);
			token_number++;
		}
		else if (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT)
			token_number = 0;
		if (token_number == 3 || arrow->type == 10)
			ft_fprintf(2, "le minishell: syntax error near unexpected token `%s'\n", arrow->content);
		i++;
		arrow = arrow->forward;
	}
}

/*if double qoute trim them and then join with ... */
