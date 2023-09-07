/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:57:12 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/07 18:38:09 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_fds(int *fds, int nb)
{
	int	i;
	
	i = 0;
	while (i < nb)
	{
		close(fds[i]);
		i++;
	}
}

void	wait_procs(int	procs)
{
	procs = 0;
	// while(procs)
	// {
		wait(NULL);
	// 	procs--;
	// }
}


void	multi_cmd(t_token **data, t_env **env, int nbr_pipes)
{
	int *fd;
	int i;

	(void)env;
	fd = malloc(sizeof(int) * (nbr_pipes * 2));
	if (!fd)
		return ;
	i = 0;
	while (i < nbr_pipes * 2)
	{
		pipe(&fd[i]);
		i += 2;
	}
	i = 0;
	t_token *tmp  = *data;
	while(tmp)
	{
		if (!fork())
		{
			if (tmp->forward)
				dup2(fd[i + 1], STDOUT_FILENO);
			if(i)
				dup2(fd[i - 2], STDIN_FILENO);
			close_fds(fd, (nbr_pipes * 2));
			one_cmd(data, tmp->content, env);
			exit(0);
		}
		i += 2;
		tmp = tmp->forward; 
	}
	close_fds(fd, (nbr_pipes * 2));
	wait_procs((nbr_pipes * 2));
}
