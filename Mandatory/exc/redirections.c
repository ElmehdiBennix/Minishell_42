/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:35:38 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/03 22:01:58 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int here_doc(char *str)
// {
// 	int fd_new_in;

// 	fd_new_in = open(str, O_WRONLY | O_CREAT , 0666);
// 	if (fd_new_in < 0)
// 		return -1;
// 	dup2(fd_new_in, STDIN_FILENO);
// }

int	red_open(t_token **fds, t_type red, char *f_name)
{
	if (red == GREAT)
	{
		(*fds)->fdout = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0654);
		if ((*fds)->fdout < 0)
			return (-1);	
	}
	else if (red == LESS)
	{
		(*fds)->fdin = open(f_name, O_RDONLY | O_CREAT, 0666);
		if ((*fds)->fdin < 0)
			return (-1);
	}
	else if (red == APPEND)
	{
		(*fds)->fdout = open(f_name, O_APPEND | O_CREAT, 0666);
		if ((*fds)->fdout < 0)
			return (-1);
	}
	return (0);// check abut the status
}