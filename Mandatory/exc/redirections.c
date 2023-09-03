/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:35:38 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/03 23:44:23 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int here_doc(int *fdin, char *str)
{
	char *read;
	*fdin = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC , 0666);
	if (*fdin < 0)
		return -1;
	while (1)
	{
		read = readline("> ");
		if (!read || (!ft_strcmp(read, str)))
			break;
		// ft_strjoin(read, "\n");
		ft_putstr_fd(read, *fdin);
		free(read);
	}
	free(read);
	return 0;
}

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
		(*fds)->fdin = open(f_name, O_RDONLY, 0654);
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
