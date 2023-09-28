/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:52:18 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/28 02:35:38 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	red_free(t_redirection *node, bool free_content)
{
	t_redirection	*arrow;

	arrow = node;
	while (arrow)
	{
		if (arrow->file_name && free_content == TRUE)
			free(arrow->file_name);
		arrow = arrow->next;
	}
}

void	cmd_free(t_command_table *node, bool free_content)
{
	t_command_table	*arrow;

	arrow = node;
	while (arrow)
	{
		if (arrow->cmds_array && free_content == TRUE)
		{
			free2d(arrow->cmds_array);
			red_free(arrow->redirections, 1);
		}
		arrow = arrow->forward;
	}
}

void	tok_free(t_token *node, bool free_content)
{
	t_token	*arrow;

	arrow = node;
	while (arrow)
	{
		if (arrow->content && free_content == TRUE)
			free(arrow->content);
		arrow = arrow -> forward;
	}
}

// free(arrow);
/*
	todo: free arrow
*/