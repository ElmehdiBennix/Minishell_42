/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_catcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:36:05 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/30 21:41:36 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*char_handler(char *prompt, int *i)
{
	int		moves;
	int		backward;
	t_token	*token;

	moves = 0;
	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	while (prompt[*i] && ft_iswhite_space(prompt[*i]) == FALSE
		&& ft_iseparateur(prompt[*i]) == FALSE && prompt[*i] != 39
		&& prompt[*i] != 34)
	{
		(*i)++;
		moves++;
	}
	backward = (*i) - moves;
	token->content = ft_calloc(moves + 1, sizeof(char));
	if (!token->content)
	{
		free(token);
		return (NULL);
	}
	ft_strlcpy(token->content, &prompt[backward], moves + 1);
	token->type = WORD;
	if (ft_iswhite_space(prompt[*i]) == TRUE || prompt[*i] == '\0')
		token->space_after = 1;
	else
		token->space_after = 0;
	return (token);
}

static t_token	*QUOT_handler(char *prompt, int *i, char QUOT_type)
{
	int		moves;
	int		backward;
	t_token	*token;

	moves = 0;
	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	(*i)++;
	while (prompt[*i] != QUOT_type)
	{
		(*i)++;
		moves++;
	}
	(*i)++;
	backward = (*i) - moves - 2;
	token->content = ft_calloc(moves + 3, sizeof(char));
	if (!token->content)
	{
		free(token);
		return (NULL);
	}
	ft_strlcpy(token->content, &prompt[backward], moves + 3);
	if (ft_iswhite_space(prompt[*i]) == TRUE || prompt[*i] == '\0')
		token->space_after = 1;
	else
		token->space_after = 0;
	if (QUOT_type == 39)
		token->type = SINGLE_QUOT;
	else
		token->type = DOUBLE_QUOT;
	return (token);
}

static t_token	*separateur_handler(char *prompt, int *i)
{
	int		moves;
	int		backward;
	t_token	*token;

	moves = 0;
	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
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
	if (!token->content)
	{
		free(token);
		return (NULL);
	}
	ft_strlcpy(token->content, &prompt[backward], moves + 1);
	token->type = get_type(token->content, moves);
	if (ft_iswhite_space(prompt[*i]) == TRUE || prompt[*i] == '\0')
		token->space_after = 1;
	else
		token->space_after = 0;
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
	while (prompt[i] && err == 0) // name error numbers in defs
	{
		if (ft_iswhite_space(prompt[i]) == TRUE)
			i++;
		else if (prompt[i] == '|' || prompt[i] == '<' || prompt[i] == '>')
			err = ft_lstdoubly(&tokens, separateur_handler(prompt, &i)); // if returns null free all prev nodes and return (NULL);
		else if (prompt[i] == 34 || prompt[i] == 39)
			err = ft_lstdoubly(&tokens, QUOT_handler(prompt, &i, prompt[i]));
		else
			err = ft_lstdoubly(&tokens, char_handler(prompt, &i)); // can optimize this after
	}
	free(prompt);
	if (err == TRUE)
		return (1);
	var->tokens = tokens;
	return (0);
}
