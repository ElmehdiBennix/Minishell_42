/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:43:06 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 22:48:12 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	one_cmd_exec(t_mini_data *var)
{
	t_command_table	*cmd;
	int				ret;

	cmd = var->exec_data;
	ret = one_cmd(cmd, &var->env_var);
	if (ret == 2)
	{
		if (cmd->cmds_array && g_err == 0)
			g_err = 127;
	}
	else if (ret == 3)
		g_err = 1;
	else
		g_err = 0;
}

void	multi_cmd_exec(t_mini_data *var)
{
	t_command_table	*m_cmd;
	int				flg_issued;

	m_cmd = var->exec_data;
	flg_issued = 0;
	while (m_cmd && m_cmd->cmds_array == NULL)
	{
		var->nodes--;
		flg_issued = 1;
		m_cmd = m_cmd->forward;
	}
	if (var->nodes)
	{
		if ((multi_cmd(m_cmd, &var->env_var)) == 1)
		{
			if (!g_err)
				g_err = 127;
		}
		else
		{
			if (!flg_issued)
				g_err = 0;
		}
	}
}
void	open_red_exec(t_mini_data *var)
{
	t_command_table	*data_iter;
	int				return_type;

	return_type = 0;
	data_iter = var->exec_data;
	while (data_iter)
	{
		return_type = open_red(data_iter);
		if (return_type == 1)
			break ;
		else if (return_type == 2)
			g_err = 1;
		data_iter = data_iter->forward;
	}
}

void	close_red_exec(t_mini_data *var)
{
	t_command_table	*data_iter;

	data_iter = var->exec_data;
	while (var->nodes != 0)
	{
		if (data_iter->fdout != 1)
			close(data_iter->fdout);
		if (data_iter->fdin != 0)
			close(data_iter->fdin);
		data_iter = data_iter->forward;
		var->nodes--;
	}
}
