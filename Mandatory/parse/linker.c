/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 04:08:32 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 06:20:17 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	fill_cmds_array(t_token **toks, t_command_table **exec, int *i)
{
	char	*buffer;

	buffer = NULL;
	while ((*toks)->type >= WORD && (*toks)->type <= DOUBLE_QUOT
		&& (*toks)->space_after == FALSE)
	{
		buffer = join_it(buffer, (*toks)->content, 1);
		(*toks) = (*toks)->forward;
		if ((*toks)->type >= PIPE && (*toks)->type <= HERE_DOC)
		{
			(*exec)->cmds_array[*i] = buffer;
			(*i)++;
		}
	}
	if ((*toks)->type >= WORD && (*toks)->type <= DOUBLE_QUOT
		&& (*toks)->space_after == TRUE)
	{
		buffer = join_it(buffer, (*toks)->content, 1);
		(*exec)->cmds_array[*i] = buffer;
		(*i)++;
		(*toks) = (*toks)->forward;
	}
}

static void	fill_redirection(t_token **toks, t_redirection **redi)
{
	char	*buffer;

	buffer = NULL;
	(*redi)->r_type = (*toks)->type;
	(*toks) = (*toks)->forward;
	while ((*toks)->type >= WORD && (*toks)->type <= DOUBLE_QUOT
		&& (*toks)->space_after == FALSE)
	{
		buffer = join_it(buffer, (*toks)->content, 1);
		(*toks) = (*toks)->forward;
		if ((*toks)->type >= PIPE && (*toks)->type <= HERE_DOC)
		{
			(*redi)->file_name = buffer;
			(*redi) = (*redi)->next;
		}
	}
	if ((*toks)->type >= WORD && (*toks)->type <= DOUBLE_QUOT
		&& (*toks)->space_after == TRUE)
	{
		buffer = join_it(buffer, (*toks)->content, 1);
		(*redi)->file_name = buffer;
		(*redi) = (*redi)->next;
		(*toks) = (*toks)->forward;
	}
}

bool	linker(t_mini_data *var)
{
	int				i;
	t_token			*toks;
	t_command_table	*exec;
	t_redirection	*redi;

	i = 0;
	toks = var->tokens;
	exec = var->exec_data;
	redi = exec->redirections;
	while (exec && toks)
	{
		if (toks->type >= WORD && toks->type <= DOUBLE_QUOT)
			fill_cmds_array(&toks, &exec, &i);
		else if (toks->type >= GREAT && toks->type <= HERE_DOC)
			fill_redirection(&toks, &redi);
		else if (toks->type == PIPE)
		{
			i = 0;
			exec = exec->forward;
			toks = toks->forward;
			redi = exec->redirections;
		}
	}
	return (tok_free(var->tokens, 1), 0);
}
