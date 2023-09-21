/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:41:44 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/15 06:17:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

t_token	*ft_lstnew_token(char **cmd_args)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->content = cmd_args;
	node->forward = NULL;
	node->fdin = 0;
	node->fdout = 1;
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

t_token *fake_struct(char **cmd)
{
	t_token	*token;
	t_token	*new_token;
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