/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:57:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/03 01:21:50 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	multi_cmd(t_command_table *exec_data, t_env **env)
{
	t_command_table	*arrow;
	int				fd[2];
	pid_t			*pid;
	int				i;
	int				status;
	int				save;

	arrow = exec_data;
	pid = ft_calloc(sizeof(pid_t), (exec_data->var->nodes));
	save = dup(0);
	i = 0;
	if (!arrow->cmds_array)
		return -1;
	while (arrow)
	{
		if (!arrow->cmds_array[0])
			return (1);
		if (!ft_strcmp(arrow->cmds_array[0], "cd"))
			ft_bultin(arrow, env);
		pipe(fd);
		pid[i] = fork();
		if (!pid[i])
		{
			signal(SIGQUIT, SIG_DFL);
			if (isatty(STDIN_FILENO) == 0)
				dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0644));
			if (pid[i] == -1)
			{
				printf("le minishell: fork: Resource\
						temporarily unavailable \n");
				return (1);
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
					exit(1);
			}
			exit(0);
		}
		if (arrow->forward)
			dup2(fd[0], STDIN_FILENO);
		else
			close(STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		i++;
		arrow = arrow->forward;
	}
	dup2(save, STDIN_FILENO);
	close(save);
	i = 0;
	while (i < exec_data->var->nodes && pid[i])
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}
