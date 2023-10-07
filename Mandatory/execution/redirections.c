/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:35:38 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 21:38:11 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	here_doc(int *fdin, char *str, char **f_name, t_mini_data *var)
{
	*f_name = herdoc_name();
	*fdin = open((*f_name), O_RDWR | O_CREAT | O_TRUNC, 0654);
	if (*fdin < 0)
		return (-1);
	write_into_fd(str, fdin, var);
	close(*fdin);
	return (0);
}

int	red_open(int *fds, t_type red, char *f_name)
{
	if (red == GREAT)
	{
		*fds = open(f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fds < 0)
			return (-1);
	}
	else if (red == LESS)
	{
		*fds = open(f_name, O_RDONLY, 0644);
		if (*fds < 0)
			return (-1);
	}
	else if (red == APPEND)
	{
		*fds = open(f_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (*fds < 0)
			return (-1);
	}
	else if (red == HERE_DOC)
	{
		*fds = open(f_name, O_RDONLY, 0644);
		if (*fds < 0)
			return (-1);
	}
	return (0);
}

int	loop_init_red(t_redirection *red, t_command_table *exec_data, int *status,
		char *f_name)
{
	if (red->r_type == GREAT)
		*status = red_open(&exec_data->fdout, GREAT, red->file_name);
	if (red->r_type == LESS)
		*status = red_open(&exec_data->fdin, LESS, red->file_name);
	else if (red->r_type == APPEND)
		*status = red_open(&exec_data->fdout, APPEND, red->file_name);
	else if (red->r_type == HERE_DOC)
	{
		here_doc(&exec_data->fdin, red->file_name, &f_name, exec_data->var);
		*status = red_open(&exec_data->fdin, HERE_DOC, f_name);
		free(f_name);
	}
	return (0);
}

void	free_red(t_redirection *red, t_command_table *red_table)
{
	if (red->file_name)
		free(red->file_name);
	if (red_table->cmds_array)
		free2d(red_table->cmds_array);
	red_table->cmds_array = NULL;
	red_table->fdin = 0;
	free(red);
}

int	open_red(t_command_table *exec_data)
{
	t_redirection	*red;
	int				status;
	char			*f_name;

	f_name = NULL;
	status = 0;
	red = exec_data->redirections;
	while (red && (status >= 0))
	{
		if (loop_init_red(red, exec_data, &status, f_name) == 1)
			return (1);
		if (status < 0)
		{
			ft_fprintf(2, "%s: No such file or directory\n", red->file_name);
			free_red(red, exec_data);
			return (2);
		}
		red = red->next;
	}
	return (0);
}
