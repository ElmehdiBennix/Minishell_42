/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:57:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/30 22:09:16 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	multi_cmd(t_command_table *exec_data, t_env **env)
{
	t_command_table	*arrow;
	int				fd[2];
	pid_t			pid;
	int				save;

	arrow = exec_data;
	save = dup(0);
	while (arrow)
	{
		if (!arrow->cmds_array[0])
			return ;
		if (!ft_strcmp(arrow->cmds_array[0], "cd"))
			ft_bultin(arrow, env);
		pipe(fd);
		pid = fork();
		if (!pid)
		{
			signal(SIGQUIT, SIG_DFL);
			if (isatty(STDIN_FILENO) == 0)
				dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0644));
			if (pid == -1)
			{
				printf("le minishell: fork: Resource\
						temporarily unavailable \n");
				return ;
			}
			if (arrow->fdin != 0)
			{
				dup2(arrow->fdin, STDIN_FILENO);
				close(arrow->fdin);
			}
			if (arrow->forward && (arrow->fdout == 1))
				dup2(fd[1], STDOUT_FILENO);
			if (arrow->fdout != 1)
			{
				dup2((arrow)->fdout, STDOUT_FILENO);
				close((arrow)->fdout);
			}
			close(fd[1]);
			close(fd[0]);
			if (is_bult_in(arrow->cmds_array[0]) == TRUE)
				ft_bultin(arrow, env);
			else
			{
				if (excute_one_cmd(arrow->cmds_array, env) == 2)
					exit(0);
			}
			exit(0);
		}
		if (arrow->forward)
			dup2(fd[0], STDIN_FILENO);
		else
			close(STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		arrow = arrow->forward;
	}
	dup2(save, STDIN_FILENO);
	close(save);
	while (wait(NULL) != -1)
		;
}
