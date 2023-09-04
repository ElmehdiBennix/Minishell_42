/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:04:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/03 15:19:35 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



bool	group_args(t_mini_data *var) // if there is no after space join them else add it to the char **
{
    int i;
    int j = 0;
	t_command_table *exec;
    t_command_table *node;
    t_token *arrow = var->tokens;

	i = 0;
	exec = NULL;
	while (i < var->nodes)
	{
        node = ft_calloc(sizeof(t_command_table),1);
        // if ( fails //)
        while (arrow)
        {
            if (arrow->type >= 5 && arrow->type <= 8)
                j++;
            if (arrow->type == PIPE)
                break;
            arrow = arrow->forward;
        }
        node->redir = 
        ft_lstdoubly(&exec,node);
        i++;
	}
	// return ();
}

// bennix@MehdiPC:~/myProjects/Minishell$ ls >| catt "-la" special case handle like there isnt a pipe there ;3