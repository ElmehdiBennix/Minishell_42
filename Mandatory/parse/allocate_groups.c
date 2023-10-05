/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_groups.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:04:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 23:20:01 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	create_redirection(t_command_table *node, int red_nbr)
{
	int				i;
	t_redirection	*red_ptr;
	t_redirection	*tmp;

	i = -1;
	while (++i < red_nbr)
	{
		red_ptr = ft_calloc(sizeof(t_redirection), 1);
		if (!red_ptr)
			return (1);
		red_ptr->file_name = NULL;
		if (i == 0)
			node->redirections = red_ptr;
		else
			tmp->next = red_ptr;
		tmp = red_ptr;
		red_ptr = red_ptr->next;
	}
	return (0);
}

static t_command_table	*create_node(t_token **tokens, t_command_table *node)
{
	int	count[2];

	ft_bzero(&count, sizeof(int) * 2);
	while (*tokens)
	{
		if (((*tokens)->type >= WORD && (*tokens)->type <= DOUBLE_QUOT)
			&& ((*tokens)->space_after || ((*tokens)->forward->type >= PIPE
					&& (*tokens)->forward->type <= HERE_DOC)))
			count[0]++;
		else if ((*tokens)->type >= GREAT && (*tokens)->type <= HERE_DOC)
			count[1]++;
		else if ((*tokens)->type == PIPE)
		{
			(*tokens) = (*tokens)->forward;
			break ;
		}
		(*tokens) = (*tokens)->forward;
	}
	node->cmds_array = ft_calloc(sizeof(char *), count[0] - count[1] + 1);
	if (!node->cmds_array)
		return (NULL);
	if (create_redirection(node, count[1]) == TRUE)
		return (free2d(node->cmds_array),
			red_free(node->redirections, 0), NULL);
	return (node);
}

bool	allocate_groups(t_mini_data *var)
{
	int				i;
	t_token			*arrow;
	t_command_table	*node;

	i = -1;
	arrow = var->tokens;
	while (++i < var->nodes)
	{
		node = ft_calloc(sizeof(t_command_table), 1);
		if (!node)
			return (1);
		node->var = var;
		node->redirections = NULL;
		node->fdin = 0;
		node->fdout = 1;
		if (cmds_doubly(&var->exec_data, create_node(&arrow, node)) == TRUE)
			return (free(node), 1);
		node = NULL;
	}
	return (0);
}
