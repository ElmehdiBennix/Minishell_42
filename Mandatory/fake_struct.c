/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:41:44 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/30 01:13:11 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

t_type check_wich_type(char *word)
{
	if (!ft_strcmp(word, ">"))
		return GREAT;
	else if (!ft_strcmp(word, "<"))
		return LESS;
	else if (!ft_strcmp(word, "<<"))
		return APPEND;
	else if (!ft_strcmp(word, ">>"))
		return HERE_DOC;
	else
		return WORD;
}

t_token	*ft_lstnew_token(int id, char *value, t_type type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->id = id;
	node->content = value;
	node->type = type;
	node->forward = NULL;
	node->backward = NULL;
	return (node);
}

t_token	*ft_lstlast_token(t_token *node)
{
	if (!node)
		return NULL;
	if (node->forward == NULL)
		return node;
	while (node->forward)
		node = node->forward;
	return node;
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*arrow;

	if (*lst == NULL)
		*lst = new;
	else
	{
		arrow = ft_lstlast_token(*lst);
		arrow->forward = new;
		new->backward = arrow; 
	}
}

t_token *fake_struct(char **cmds, t_env *env)
{
	t_token	*token;
	t_token	*new_token;
	int 	i;

	(void)env;
	if (*cmds == NULL)
		return NULL;
	else
	{
		i = 0;
		token = NULL;
		while (cmds[i])
			i++;
		i = 0;
		while (cmds[i])
		{
			new_token = ft_lstnew_token(i + 1, cmds[i], check_wich_type(cmds[i]));
			ft_lstadd_back_token(&token, new_token);
			i++;
		}
		return token;
	}
}