/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:35:38 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/01 01:36:05 by otaraki          ###   ########.fr       */
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

int red_open(t_type red, char *f_name)
{
	int fd = 0;

	if (red == GREAT)
	{
		fd = open(f_name, O_WRONLY | O_CREAT, 0666);
		if (fd < 0)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (-2);	
	}
	else if (red == LESS)
	{
		fd = open(f_name, O_RDONLY | O_CREAT, 0666);
		if (fd < 0)
			return (-1);
		if (dup2(fd, STDIN_FILENO))
			return (-2);
	}
	else if (red == APPEND)
	{
		fd = open(f_name, O_APPEND | O_CREAT, 0666);
		if (fd < 0)
			return (-1);
		if (dup2(fd, STDOUT_FILENO))
			return (-2);
	}
	return (fd);
}