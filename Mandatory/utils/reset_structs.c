/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:52:18 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/05 07:30:43 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tok_free(t_token *head, bool free_content)
{
	if (head == NULL)
		return ;
	tok_free(head->forward, free_content);
	if (free_content == TRUE && head->content != NULL)
	{
		free(head->content);
		head->content = NULL;
	}
	free(head);
}

void	red_free(t_redirection *head, bool free_content)
{
	if (head == NULL)
		return ;
	red_free(head->next, free_content);
	if (free_content == TRUE && head->file_name != NULL)
	{
		free(head->file_name);
		head->file_name = NULL;
	}
	free(head);
}

void	cmd_free(t_command_table *head, bool free_content)
{
	if (head == NULL)
		return ;
	cmd_free(head->forward, free_content);
	if (free_content == TRUE && head->cmds_array != NULL)
	{
		free2d(head->cmds_array);
		head->cmds_array = NULL;
		red_free(head->redirections, TRUE);
	}
	free(head);
}
