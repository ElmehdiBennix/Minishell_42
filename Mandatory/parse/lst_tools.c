/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:21:30 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/06 00:32:41 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*join_it(char *s1, char *s2, int flag)
{
	char	*new_string;
	char	*tmp1;
	char	*tmp2;

	tmp1 = s1;
	tmp2 = s2;
	new_string = ft_strjoin(s1, s2);
	if (flag == 1)
		return (free(tmp1), new_string);
	else if (flag == 2)
		return (free(tmp2), new_string);
	else if (flag == 3)
		return (free(tmp1), free(tmp2), new_string);
	return (new_string);
}

bool	toks_doubly(t_token **head, t_token *node)
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

bool	cmds_doubly(t_command_table **head, t_command_table *node)
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
