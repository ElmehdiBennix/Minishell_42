/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:57:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/21 06:53:23 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	multi_cmd(t_command_table *exec_data, t_env *env)
{
	t_command_table		*arrow;
	int			        fd[2];
	pid_t		        pid;
	int			        save;

	arrow	= exec_data;
	save = dup(0);
	while(arrow)
	{
		if (!arrow->cmds_array[0])
			return ;
		if (!ft_strcmp(arrow->cmds_array[0], "cd"))
			ft_bultin(arrow, env); // catch errors
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			// if (arrow->fdin != 0)
			// {
			// 	dup2(arrow->fdin, STDIN_FILENO);
			// 	close(arrow->fdin);
			// }
			// if (arrow->forward && arrow->fdout == 1)
			// 	dup2(fd[1], STDOUT_FILENO);
			// if (arrow->fdout != 1)
			// {
			// 	dup2((arrow)->fdout, STDOUT_FILENO);
			// 	close((arrow)->fdout);
			// }
			// close(fd[1]);
			// close(fd[0]);
			if (is_bult_in(arrow->cmds_array[0]) == TRUE)
				ft_bultin(arrow, env);
			else
			{
				if (excute_one_cmd(arrow->cmds_array, env) == 2)
					exit(0); // ask about it ***** 
			}
			exit(0); // take it off
		}
		// if (arrow->forward)
		// 	dup2(fd[0], STDIN_FILENO);
		// else
		// 	close(STDIN_FILENO);
		// close(fd[0]);
		// close(fd[1]);
		arrow = arrow->forward;
	}
	// dup2(save, STDIN_FILENO);
	// close(save);
	while (wait(NULL) != -1)
		;
}

// void	multi_cmd(t_token **data, t_env **env, int nbr_pipes)
// {

// 	int	forked;
	
// 	(void)env;
// 	(void)nbr_pipes;
// 	t_token *tmp  = *data;

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
