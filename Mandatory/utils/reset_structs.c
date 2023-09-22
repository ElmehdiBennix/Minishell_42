/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:52:18 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/22 06:25:04 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	free_array(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// }

// void	free_struct_env(t_env *env)
// {
// 	while(env != NULL)
// 	{
// 		if (env->key != NULL)
// 			free(env->key);
// 		if (env->value != NULL)
// 			free(env->value);
// 		env = env->next;
// 	}
// }

// void	free_struct_data(t_token *token)
// {
// 	while(token != NULL)
// 	{
// 		if (token->content)
// 			free_array(token->content);
// 		token = token->forward;
// 	}
// }

void	token_free(t_token *node , bool free_content)
{
	t_token     *arrow;

	arrow = node;
	while (arrow)
	{
        if (free_content == TRUE)
            free(arrow->content);
		free(arrow);
		arrow = arrow -> forward;
	}
}