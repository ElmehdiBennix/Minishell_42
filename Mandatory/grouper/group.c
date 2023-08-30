/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:04:51 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/30 00:33:03 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static  int ft_lstsizee(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
        if (lst->type != PIPE)
		    i++;
		lst = lst -> forward;
	}
	return (i);
}

bool group_args(t_mini_data *var)
{
    int size = ft_lstsizee(var->tokens);
    printf("%d\n",size);
    
    
}