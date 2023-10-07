/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:31:53 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 21:35:31 by otaraki          ###   ########.fr       */
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

void	print_err(void)
{
	ft_fprintf(2, "le minishell: fork: Resource\
			temporarily unavailable \n");
	return ;
}
