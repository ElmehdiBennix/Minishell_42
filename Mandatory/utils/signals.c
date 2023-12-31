/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:38:47 by bennix            #+#    #+#             */
/*   Updated: 2023/10/07 23:08:45 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_handler(int signal)
{
	(void)signal;
	if (waitpid(-1, NULL, WNOHANG) == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_err = 1;
	}
}

int	herdoc_helper(void)
{
	if (isatty(STDIN_FILENO) == 0)
	{
		dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0644));
		return (1);
	}
	return (0);
}

void	fhandler(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
}
