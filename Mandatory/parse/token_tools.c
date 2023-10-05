/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:21:30 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 07:27:47 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_iseparateur(char c)
{
	if (c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

int	ft_iswhite_space(char c)
{
	if (c == ' ' || c == '\r' || c == '\n' || c == '\f' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

t_type	get_type(char *token, int moves)
{
	if (moves == 1)
	{
		if (*token == '|')
			return (PIPE);
		else if (*token == '>')
			return (GREAT);
		else if (*token == '<')
			return (LESS);
	}
	else
	{
		if (ft_strncmp(token, ">>", 2) == 0)
			return (APPEND);
		else if (ft_strncmp(token, "<<", 2) == 0)
			return (HERE_DOC);
	}
	return (10);
}

int	ft_lstdoubly(t_token **head, t_token *node)
{
	t_token	*arrow;

	arrow = *head;
	if (node == NULL)
		return (1);
	else if (*head == NULL)
		*head = node;
	else
	{
		while (arrow->forward != NULL)
			arrow = arrow->forward;
		arrow->forward = node;
		node->backward = arrow;
		node->forward = NULL;
	}
	return (0);
}

int	multi_key(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c < 123) || (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

int	single_key(int c)
{
	if (c == '?' || c == '@' || c == '#' || c == '$' || c == '-' || c == '&'
		|| c == '*' || c == ';' || c == '!' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

bool	ft_lstcmds(t_command_table **head, t_command_table *node)
{
	t_command_table	*arrow;

	arrow = *head;
	if (node == NULL)
		return (1);
	else if (*head == NULL)
	{
		*head = node;
		node->forward = NULL;
		node->backward = NULL;
	}
	else
	{
		while (arrow->forward != NULL)
			arrow = arrow->forward;
		arrow->forward = node;
		node->backward = arrow;
		node->forward = NULL;
	}
	return (0);
}
