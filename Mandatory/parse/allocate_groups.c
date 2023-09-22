/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_groups.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:04:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/22 08:36:20 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool ft_lstcmds(t_command_table **head, t_command_table *node) 
{
    t_command_table *arrow = *head;

    if (node == NULL)
        return 1;
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
    return 0;
}

t_command_table *create_node(t_token **tokens)
{
    int i = 0;
    int j = 0;
    t_command_table *node;
    node = ft_calloc(sizeof(t_command_table),1);
    //if ( fails //)

    while ((*tokens))
    {
        if (((*tokens)->type >= WORD && (*tokens)->type <= DOUBLE_QUOT) && (*tokens)->space_after == 1)
            i++;
        else if ((*tokens)->type >= GREAT && (*tokens)->type <= HERE_DOC)
            j++;
        else if ((*tokens)->type == PIPE)
        {
            (*tokens) = (*tokens)->forward;
            break;
        }
        (*tokens) = (*tokens)->forward;
    }
    node->cmds_array = ft_calloc(sizeof(char *),i-j+1);
    //if failed ret
    i = -1;
    t_redirection *red_ptr;
    t_redirection *tmp;
    while(++i < j)
    {
        red_ptr = ft_calloc(sizeof(t_redirection),1);
        // if failed
        if (i == 0)
            node->redirections = red_ptr;
        else
            tmp->next = red_ptr;
        // red_ptr->fd = i;
        tmp = red_ptr;
        red_ptr = red_ptr->next;
    }
    return (node);

}

bool	allocate_groups(t_mini_data *var)
{
    int i;
    t_token *arrow = var->tokens;
    t_command_table *test;

	i = -1;
	while (++i < var->nodes)
	{
        test = create_node(&arrow); // if this gives null fail
        test->var = var;
        if(ft_lstcmds(&var->exec_data,test) == TRUE)
            return(1);
	}
	return (0);
}
