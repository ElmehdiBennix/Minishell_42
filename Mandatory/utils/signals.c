/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:38:47 by bennix            #+#    #+#             */
/*   Updated: 2023/10/06 20:56:20 by ebennix          ###   ########.fr       */
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
