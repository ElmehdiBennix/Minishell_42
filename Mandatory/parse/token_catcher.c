/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_catcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/05 23:08:33 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*create_token(char *prompt, int i, int moves, int backward)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->content = ft_calloc(moves, sizeof(char));
	if (!token->content)
		return (free(token), NULL);
	ft_strlcpy(token->content, &prompt[backward], moves);
	if (ft_iswhite_space(prompt[i]) == TRUE || prompt[i] == '\0')
		token->space_after = 1;
	else
		token->space_after = 0;
	return (token);
}

static t_token	*char_handler(char *prompt, int *i)
{
	int		moves;
	int		backward;
	t_token	*token;

	moves = 0;
	while (prompt[*i] && ft_iswhite_space(prompt[*i]) == FALSE
		&& ft_iseparateur(prompt[*i]) == FALSE && prompt[*i] != 39
		&& prompt[*i] != 34)
	{
		(*i)++;
		moves++;
	}
	backward = (*i) - moves;
	token = create_token(prompt, *i, moves + 1, backward);
	if (token)
		token->type = WORD;
	return (token);
}

static t_token	*quot_handler(char *prompt, int *i, char quot_type)
{
	int		moves;
	int		backward;
	t_token	*token;

	moves = 0;
	(*i)++;
	while (prompt[*i] != quot_type)
	{
		(*i)++;
		moves++;
	}
	(*i)++;
	backward = (*i) - moves - 2;
	token = create_token(prompt, *i, moves + 3, backward);
	if (token && quot_type == 39)
		token->type = SINGLE_QUOT;
	else if (token && quot_type == 34)
		token->type = DOUBLE_QUOT;
	return (token);
}

static t_token	*separateur_handler(char *prompt, int *i)
{
	int		moves;
	int		backward;
	t_token	*token;

	moves = 0;
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
	token = create_token(prompt, *i, moves + 1, backward);
	if (token)
		token->type = get_type(token->content, moves);
	return (token);
}

bool	token_catcher(char *prompt, t_mini_data *var)
{
	int		i;
	int		err;
	t_token	*tokens;

	tokens = NULL;
	i = 0;
	err = 0;
	while (prompt[i] && err == 0)
	{
		if (ft_iswhite_space(prompt[i]) == TRUE)
			i++;
		else if (prompt[i] == '|' || prompt[i] == '<' || prompt[i] == '>')
			err = toks_doubly(&tokens, separateur_handler(prompt, &i));
		else if (prompt[i] == 34 || prompt[i] == 39)
			err = toks_doubly(&tokens, quot_handler(prompt, &i, prompt[i]));
		else
			err = toks_doubly(&tokens, char_handler(prompt, &i));
	}
	free(prompt);
	var->tokens = tokens;
	if (err == TRUE)
		return (1);
	return (0);
}
