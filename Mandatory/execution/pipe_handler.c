/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:57:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/06 19:45:58 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	dup_fdin(int *fdin)
{
	if (*fdin != 0)
	{
		dup2(*fdin, STDIN_FILENO);
		close(*fdin);
	}
}

void	dup_fdout(int *fdout)
{
	if (*fdout != 1)
	{
		dup2(*fdout, STDOUT_FILENO);
		close(*fdout);
	}
}

void	close_pipe_fds(int fd[])
{
	close(fd[1]);
	close(fd[0]);
}

void	child_process(t_command_table *arrow, int fd[], t_env **env)
{
	int	returned;

	returned = 0;
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
	exit(EXIT_FAILURE);
}

void	print_err(void)
{
	printf("le minishell: fork: Resource\
			temporarily unavailable \n");
	return ;
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
		if (arrow->cmds_array && !ft_strcmp(arrow->cmds_array[0], "cd"))
			ft_bultin(arrow, env);
		pipe(fd);
		forked = fork();
		if (forked == -1)
			print_err();
		if (!forked)
		{
			signal(SIGQUIT, SIG_DFL);
			child_process(arrow, fd, env);
		}
		parent_process(arrow, fd, &status);
		arrow = arrow->forward;
	}
	dup_fdin(&save);
	while (wait(NULL) != -1)
		;
	return (WEXITSTATUS(status));
}
