/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:35:59 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 23:09:11 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*herdoc_name(void)
{
	int		i;
	char	*s;
	char	*n;

	i = 0;
	n = ft_itoa(i);
	s = ft_strjoin("/tmp/here_doc", n);
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
	return (s);
}

void	write_into_fd(char *str, int *fdin, t_mini_data *var)
{
	char	*rd;
	char	*line;

	while (1)
	{
		signal(SIGINT, fhandler);
		rd = readline("> ");
		if (herdoc_helper())
			break ;
		if (!rd)
			break ;
		line = rd;
		rd = get_value(rd, var);
		free(line);
		if (!ft_strcmp(rd, str))
		{
			free(rd);
			break ;
		}
		rd = join_it(rd, "\n", 1);
		ft_fprintf(*fdin, "%s", rd);
		free(rd);
		rd = NULL;
	}
}
