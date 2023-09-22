/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 04:08:32 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/22 08:37:51 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	linker(t_mini_data *var)
{
    int i = 0;
    t_token *arrow = var->tokens;
    t_command_table *exec = var->exec_data;
    t_redirection   *redirec = exec->redirections;
    char *buffer ;

    while (exec && arrow)
    {
        buffer = NULL;
        if (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT)
        {
            while (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT && arrow->space_after == FALSE)
            {
                buffer = ft_strjoin(buffer,arrow->content);
                arrow = arrow->forward;
            }
            if (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT && arrow->space_after == TRUE)
            {
                buffer = ft_strjoin(buffer,arrow->content);
                exec->cmds_array[i] = buffer;
                i++;
                arrow = arrow->forward;
            }
        }
        else if (arrow->type >= GREAT && arrow->type <= HERE_DOC)
        {
            redirec->r_type = arrow->type;
            arrow = arrow->forward;
            while (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT && arrow->space_after == FALSE)
            {
                buffer = ft_strjoin(buffer,arrow->content);
                arrow = arrow->forward;
            }
            if (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT && arrow->space_after == TRUE)
            {
                redirec->file_name = ft_strjoin(buffer,arrow->content);
                redirec = redirec->next;
                arrow = arrow->forward;
            }
        }
        else if (arrow->type == PIPE)
        {
            i = 0;
            exec = exec->forward;
            arrow = arrow->forward;
            redirec = exec->redirections;
        }
    }
}
