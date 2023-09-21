/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:35:38 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/20 21:00:56 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *herdoc_name()
{
	int i = 0;
	char *s = ft_strjoin("/tmp/here_doc", ft_itoa(i));
	while (access(s, F_OK) == 0)
	{
		free(s);
		i++;
		s = ft_strjoin("/tmp/here_doc", ft_itoa(i));
	}
	return s;
}

int here_doc(int *fdin, char *str, char **f_name)
{
	char			*rd;

	*f_name = herdoc_name();
	*fdin = open((*f_name), O_RDWR | O_CREAT | O_TRUNC, 0654);
	if (*fdin < 0)
		return -1;
	while (1)
	{
		rd = readline(">");
		if (!rd || (!ft_strcmp(rd, str)))
			break;
		rd = ft_strjoin(rd, "\n");
		ft_putstr_fd(rd, *fdin);
		free(rd);
	}
	free(rd);
	close(*fdin);
	return 0;
}

int	red_open(int *fds, t_type red, char *f_name)
{
	if (red == GREAT)
	{
		*fds = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0654);
		if (*fds < 0)
			return (-1);
	}
	else if (red == LESS)
	{
		*fds = open(f_name, O_RDONLY, 0654);
		if (*fds < 0)
			return (-1);
	}
	else if (red == APPEND)
	{
		*fds = open(f_name, O_APPEND | O_WRONLY | O_CREAT, 0654);
		if (*fds < 0)
			return (-1);
	}
	else if (red == HERE_DOC)// need to check on signles
	{
		*fds = open(f_name, O_RDONLY, 0654);
		if (*fds < 0)
			return (-1);

			
	}
	return (0);
}


void	open_red(t_token **data, char **cmds)
{
	size_t	i;
	int		status;
	char 	*f_name;

	i = 0;
	f_name = NULL;
	status = 0;
	while(cmds[i] && (status >= 0))
	{
		if (!ft_strcmp(cmds[i], ">"))
		{
			status = red_open(&(*data)->fdout, GREAT, cmds[i + 1]);
			free(cmds[i]);
			cmds[i] = NULL;
		}
		else if (!ft_strcmp(cmds[i], "<"))
		{
			status = red_open(&(*data)->fdin, LESS, cmds[i + 1]);
			free(cmds[i]);
			cmds[i] = NULL;
		}
		else if (!ft_strcmp(cmds[i], ">>"))
		{
			status = red_open(&(*data)->fdout, APPEND, cmds[i + 1]);
			free(cmds[i]);
			cmds[i] = NULL;
		}
		else if (!ft_strcmp(cmds[i], "<<"))
		{
			here_doc(&(*data)->fdin ,cmds[i + 1], &f_name);
			status = red_open(&(*data)->fdin, HERE_DOC, f_name);
			free(f_name);
			free(cmds[i]);
			cmds[i] = NULL;
		}
		if (status < 0)// segfault when given an invalide file in 
		{
			printf("%s: No such file or directory\n", cmds[i + 1]);
			free((*data)->content[0]);
			(*data)->content[0] = NULL;
			(*data)->fdin = 0;
			return ;
		}
		++i;
	}
}