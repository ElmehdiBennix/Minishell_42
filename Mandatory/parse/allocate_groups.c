/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_groups.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:04:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/22 05:29:00 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void ft_lstcmds(t_command_table **head, t_command_table *node) 
{
    t_command_table *arrow = *head;

    if (node == NULL)
        return; // error
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
        {
            // printf("content == %s , space after == %d \n",(*tokens)->content,(*tokens)->space_after);
            i++;
        }
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
    // printf("i == %d , j == %d\n",i-j , j);
    i = -1;
    t_redirection *red_ptr;
    t_redirection *tmp;
    while(++i < j)
    {
        red_ptr = ft_calloc(sizeof(t_redirection),1);
        // if failed
        if (i == 0)
            node->redir = red_ptr;
        else
            tmp->next = red_ptr;
        // red_ptr->fd = i;
        tmp = red_ptr;
        red_ptr = red_ptr->next;
    }
    return (node);

}

bool	allocate_groups(t_mini_data *var) // if there is no after space join them else add it to the char **
{
    int i;
    t_token *arrow = var->tokens;
    t_command_table *test;
    var->exec_data = NULL;

	i = -1;
	while (++i < var->nodes)
	{
        test = create_node(&arrow); // protect
        test->var = var;
        // while (test->redir)
        // {
        //     printf("red id = %d\n",test->redir->fd);
        //     test->redir = test->redir->next;
        // }
        ft_lstcmds(&var->exec_data,test);
	}
	// return ();
}
