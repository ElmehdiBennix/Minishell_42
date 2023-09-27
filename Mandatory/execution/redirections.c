/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:35:38 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/27 23:00:45 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *herdoc_name(void)
{
	int i;
	char *n;
	i = 0;
	n = ft_itoa(i);
	char *s = ft_strjoin("/tmp/here_doc", n);
	free(n);
	while (access(s, F_OK) == 0)
	{
		n = NULL;
		free(s);
		i++;
		n = ft_itoa(i);
		s = ft_strjoin("/tmp/here_doc", n);
		free(n);
	}
	return s;
}


void	fhandler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
}

// char    *get_value(char *content , t_mini_data *var); // algor wroking fine need work need to be done to make it understandable

int here_doc(int *fdin, char *str, char **f_name, t_mini_data *var) // var
{
	char			*rd;
	(void) var;
	*f_name = herdoc_name();
	*fdin = open((*f_name), O_RDWR | O_CREAT | O_TRUNC, 0654);
	if (*fdin < 0)
		return -1;
	while (1)
	{
		signal(SIGINT,fhandler); // should be in a child porcess
		rd = readline(">");
		if (!rd || !ft_strcmp(rd, str))
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
	else if (red == HERE_DOC) // need to check on signles
	{
		*fds = open(f_name, O_RDONLY, 0654);
		if (*fds < 0)
			return (-1);	
	}
	return (0);
}

int	open_red(t_command_table *exec_data)
{
	int		status;
	char 	*f_name;

	f_name = NULL;
	status = 0;
	while(exec_data->redirections && (status >= 0))
	{
		if (exec_data->redirections->r_type == GREAT)
			status = red_open(&exec_data->fdout, GREAT, exec_data->redirections->file_name);
		else if (exec_data->redirections->r_type == LESS)
			status = red_open(&exec_data->fdin, LESS, exec_data->redirections->file_name);
		else if (exec_data->redirections->r_type == APPEND)
			status = red_open(&exec_data->fdin, APPEND, exec_data->redirections->file_name);
		else if (exec_data->redirections->r_type == HERE_DOC)
		{
			here_doc(&exec_data->fdin ,exec_data->redirections->file_name, &f_name, exec_data->var);
			if (isatty(STDIN_FILENO) == 0)
			{
				dup2(STDIN_FILENO,open(ttyname(1),O_RDONLY , 0644));
				printf("dsds\n");
				return (1);
			}
			status = red_open(&exec_data->fdin, HERE_DOC, f_name);
			free(f_name);
		}
		if (status < 0)
		{
			printf("%s: No such file or directory\n", exec_data->redirections->file_name);
			if (exec_data->cmds_array)
				free(exec_data->cmds_array);
			exec_data->cmds_array = NULL;
			exec_data->fdin = 0;
			return (2);
		}
		exec_data->redirections = exec_data->redirections->next;
	}
	return (0);
	// int new_stdin = open("/dev/tty", O_RDONLY);
}