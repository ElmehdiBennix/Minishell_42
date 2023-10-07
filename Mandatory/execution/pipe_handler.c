/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:57:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 23:09:57 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_process(t_command_table *arrow, int fd[], t_env **env)
{
	int	returned;

	returned = 0;
	signal(SIGQUIT, SIG_DFL);
	dup_fdin(&arrow->fdin);
	if (arrow->forward && (arrow->fdout == 1))
		dup2(fd[1], STDOUT_FILENO);
	dup_fdout(&arrow->fdout);
	close_pipe_fds(fd);
	if (arrow->cmds_array && is_bult_in(arrow->cmds_array[0]) == TRUE)
		returned = ft_bultin(arrow, env);
	else
	{
		if (arrow->cmds_array && excute_one_cmd(arrow->cmds_array, env) == 2)
		{
			free2d(arrow->cmds_array);
			exit(EXIT_FAILURE);
		}
		else
			exit(EXIT_FAILURE);
	}
	if (returned == 0)
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

void	parent_process(t_command_table *arrow, int *fd, int *status)
{
	if (arrow->forward == NULL)
		wait(status);
	if (arrow->forward)
		dup2(fd[0], STDIN_FILENO);
	else
		close(STDIN_FILENO);
	close_pipe_fds(fd);
}

int	multi_cmd(t_command_table *exec_data, t_env **env)
{
	t_command_table	*arrow;
	int				fd[2];
	int				forked;
	int				status;
	int				save;

	arrow = exec_data;
	save = dup(0);
	while (arrow)
	{
		pipe(fd);
		forked = fork();
		if (forked == -1)
			print_err();
		if (!forked)
			child_process(arrow, fd, env);
		parent_process(arrow, fd, &status);
		arrow = arrow->forward;
	}
	dup_fdin(&save);
	while (wait(NULL) != -1)
		;
	return (WEXITSTATUS(status));
}
