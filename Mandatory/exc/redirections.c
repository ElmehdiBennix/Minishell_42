/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:35:38 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/05 23:07:28 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int here_doc(int *fdin, char *str)
{
	char	*read;
	
	*fdin = open("/tmp/here_doc", O_RDWR | O_CREAT | O_TRUNC, 0654);
	if (*fdin < 0)
		return -1;
	while (1)
	{
		read = readline("heredoc> ");
		if (!read || (!ft_strcmp(read, str)))
			break;
		read = ft_strjoin(read, "\n");
		ft_putstr_fd(read, *fdin);
		free(read);
	}
	free(read);
	close(*fdin);
	return 0;
}

int	appaned(int *fdout, char *strout)
{
	char	*line;

	*fdout = open(strout, O_APPEND | O_WRONLY | O_CREAT, 0654);
	if (*fdout < 0)
		return -1;
	while (1)
	{
		line = readline("");
		if (!line)
			break ;
		line = ft_strjoin(line, "\n");
		ft_putstr_fd(line, *fdout);
		free(line);
	}
	free(line);
	close(*fdout);
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
		(*fds)->fdout = open(f_name, O_APPEND | O_CREAT, 0654);
		if ((*fds)->fdout < 0)
			return (-1);
	}
	else if (red == HERE_DOC)
	{
		(*fds)->fdin = open(f_name, O_RDONLY, 0654);
		if ((*fds)->fdin < 0)
			return (-1);
	}
	return (0);// check abut the status
}
