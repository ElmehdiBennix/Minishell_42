/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:57:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/18 02:54:19 by ebennix          ###   ########.fr       */
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
