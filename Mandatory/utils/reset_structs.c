/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:52:18 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/25 19:59:54 by otaraki          ###   ########.fr       */
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
void	red_free(t_redirection *node , bool free_content)
{
	t_redirection     *arrow;

	arrow = node;
	while (arrow)
	{
        if (arrow->file_name && free_content == TRUE)
            free(arrow->file_name);
		// free(arrow);
		arrow = arrow->next;
	}
}

void	cmd_free(t_command_table *node , bool free_content)
{
	t_command_table     *arrow;

	arrow = node;
	while (arrow)
	{
        if (arrow->cmds_array && free_content == TRUE)
		{
            free2d(arrow->cmds_array);
			red_free(arrow->redirections,1);
		}
		// free(arrow);
		arrow = arrow->forward;
	}
}

void	tok_free(t_token *node , bool free_content)
{
	t_token     *arrow;

	arrow = node;
	while (arrow)
	{    
		if (arrow->content && free_content == TRUE)
            free(arrow->content);
		// free(arrow);
		/*
			todo: free arrow
		*/
		arrow = arrow -> forward;
	}
}