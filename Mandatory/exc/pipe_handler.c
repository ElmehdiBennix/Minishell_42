/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:57:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/18 01:56:09 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	multi_cmd(_prototype **data, t_env **env)
{
	int			fd[2];
	int			forked;
	_prototype		*tmp;
	int			save;

	(void)env;
	tmp	= *data;
	save = dup(0);
	while(tmp)
	{
		if (!ft_strcmp(tmp->content[0], "cd"))
			ft_bultin(tmp, tmp->content, env);
		pipe(fd);
		forked = fork();
		if (tmp->fdin != 0)
		{
			dup2(tmp->fdin, STDIN_FILENO);
			close(tmp->fdin);
		}
		if (!forked)
		{
			if (tmp->forward && tmp->fdout == 1)
				dup2(fd[1], STDOUT_FILENO);
			if (tmp->fdout != 1)
			{
				dup2((tmp)->fdout, STDOUT_FILENO);
				close((tmp)->fdout);
			}
			close(fd[1]);
			close(fd[0]);
			if (is_bult_in(tmp->content[0]) == TRUE)
				ft_bultin(tmp, tmp->content, env);
			else
				excute_one_cmd(data, tmp->content, env);
			exit(0);
		}
		if (tmp->forward)
			dup2(fd[0], STDIN_FILENO);
		else
			close(STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		tmp = tmp->forward;
	}
	dup2(save, STDIN_FILENO);
	close(save);
	while (wait(NULL) != -1)
		;
}

// void	multi_cmd(_prototype **data, t_env **env, int nbr_pipes)
// {

// 	int	forked;
	
// 	(void)env;
// 	(void)nbr_pipes;
// 	_prototype *tmp  = *data;

// 	int save = dup(0);
// 	int fd[2];
// 	while(tmp)
// 	{
// 		pipe(fd);
// 		forked = fork();
// 		if (!forked)
// 		{
// 			if (tmp->forward)
// 			{	
// 				if (tmp->fdout == 1){
// 					dup2(fd[1], STDOUT_FILENO);
// 				}
// 				else 
// 				{
// 					dup2((tmp)->fdout, STDOUT_FILENO);
// 					close((tmp)->fdout);
// 				}
// 			}
// 			close(fd[1]);
// 			close(fd[0]);
// 			// if (tmp->forward)
// 			// 	ft_bultin(tmp, tmp->forward->content, env);
// 			excute_one_cmd(data, tmp->content, env);
// 		}
// 		if (tmp->forward)
// 		{
// 			if (tmp->fdin == 0)
// 				dup2(fd[0], STDIN_FILENO);
// 			else
// 			{
// 				dup2((tmp)->fdin, STDIN_FILENO);		
// 				close((tmp)->fdin);
// 			}
// 		}
// 		else
// 			close(STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		tmp = tmp->forward; 
// 	}
// 	dup2(save, STDIN_FILENO);
// 	close(save);
// 	// dup2(STDIN_FILENO, save);
// 	// close_fds(fd, (nbr_pipes * 2));
// 	// waitpid(forked, NULL, 0);
// 	while (wait(NULL) != -1)
// 		;
// }
