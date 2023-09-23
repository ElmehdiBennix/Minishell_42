/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 04:08:32 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/23 21:38:22 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// bool    func(int flag)
// {
//     while (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == FALSE)
//     {
//         buffer = ft_strjoin(buffer,toks->content);
//         toks = toks->forward;
//     }
//     if (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == TRUE)
//     {
//         if(flag == )
//         {
//             buffer = ft_strjoin(buffer,toks->content);
//             exec->cmds_array[i] = buffer;
//             i++;
//             toks = toks->forward;
//         }
//         else if (flag == )
//         {
//             redi->file_name = ft_strjoin(buffer,toks->content);
//             redi = redi->next;
//             toks = toks->forward;
//         }
//     }
// }

bool	linker(t_mini_data *var)
{
    int i = 0;
    t_token *toks = var->tokens;
    t_command_table *exec = var->exec_data;
    t_redirection   *redi = exec->redirections;
    char *buffer;

    while (exec && toks)
    {
        buffer = NULL;
        if (toks->type >= WORD && toks->type <= DOUBLE_QUOT)
        {
            while (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == FALSE)
            {
                buffer = ft_strjoin(buffer,toks->content);
                toks = toks->forward;
            }
            if (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == TRUE)
            {
                buffer = ft_strjoin(buffer,toks->content);
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
                buffer = ft_strjoin(buffer,toks->content);
                toks = toks->forward;
            }
            if (toks->type >= WORD && toks->type <= DOUBLE_QUOT && toks->space_after == TRUE)
            {
                redi->file_name = ft_strjoin(buffer,toks->content);
                redi = redi->next;
                toks = toks->forward;
            }
        }
        else if (toks->type == PIPE)
        {
            i = 0;
            exec = exec->forward;
            toks = toks->forward;
            redi = exec->redirections;
        }
    }
}
