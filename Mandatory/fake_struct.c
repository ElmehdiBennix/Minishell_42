/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:41:44 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/18 01:31:54 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

_prototype	*ft_lstnew_token(char **cmd_args)
{
	_prototype	*node;

	node = (_prototype *)malloc(sizeof(_prototype));
	if (node == NULL)
		return (NULL);
	node->content = cmd_args;
	node->forward = NULL;
	node->fdin = 0;
	node->fdout = 1;
	node->backward = NULL;
	return (node);
}

_prototype	*ft_lstlast_token(_prototype *node)
{
	if (!node)
		return NULL;
	if (node->forward == NULL)
		return node;
	while (node->forward)
		node = node->forward;
	return node;
}

void	ft_lstadd_back_token(_prototype **lst, _prototype *new)
{
	_prototype	*arrow;

	if (*lst == NULL)
		*lst = new;
	else
	{
		arrow = ft_lstlast_token(*lst);
		arrow->forward = new;
		new->backward = arrow; 
	}
}

_prototype *fake_struct(char **cmd)
{
	_prototype	*token;
	_prototype	*new_token;
	char 	**cmd_args;
	int 	i;

	if (cmd == NULL)
		return NULL;
	else
	{
		i = 0;
		token = NULL;
		while (cmd[i])//ls -lR /usr/bin | sed 's/./X/6' | head -n 7
		{
			cmd_args = ft_split(cmd[i], ' ');
			new_token = ft_lstnew_token(cmd_args);
			ft_lstadd_back_token(&token, new_token);
			i++;
		}
		return token;
	}
}