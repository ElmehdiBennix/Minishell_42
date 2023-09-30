/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 04:08:32 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/30 21:43:35 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	linker(t_mini_data *var)
{
	int				i;
	t_token			*toks;
	t_command_table	*exec;
	t_redirection	*redi;
	char			*buffer;

	i = 0;
	toks = var->tokens;
	exec = var->exec_data;
	redi = exec->redirections;
	while (exec && toks)
	{
		buffer = NULL;
		if (toks->type >= WORD && toks->type <= DOUBLE_QUOT)
		{
			while (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == FALSE)
			{
				buffer = ft_strjoin(buffer, toks->content);
				toks = toks->forward;
				if (toks->type >= PIPE && toks->type <= HERE_DOC)
				{
					exec->cmds_array[i] = buffer;
					i++;
				}
			}
			if (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == TRUE)
			{
				buffer = ft_strjoin(buffer, toks->content);
				exec->cmds_array[i] = buffer;
				i++;
				toks = toks->forward;
			}
		}
		else if (toks->type >= GREAT && toks->type <= HERE_DOC)
		{
			redi->r_type = toks->type;
			toks = toks->forward;
			while (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == FALSE)
			{
				buffer = ft_strjoin(buffer, toks->content);
				toks = toks->forward;
				if (toks->type >= PIPE && toks->type <= HERE_DOC)
				{
					redi->file_name = buffer;
					redi = redi->next;
				}
			}
			if (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == TRUE)
			{
				redi->file_name = ft_strjoin(buffer, toks->content);
				redi = redi->next;
				toks = toks->forward;
			}
		}
		else if (toks->type == PIPE) // think over
		{
			i = 0;
			exec = exec->forward;
			toks = toks->forward;
			redi = exec->redirections;
		}
	}
	return (0);
}
