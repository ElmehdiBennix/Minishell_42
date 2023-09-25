/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bultins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:50:58 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/26 00:31:35 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_bultin(t_command_table *exec_data, t_env **env)
{
	static int exit_s = 0;
	if (env == NULL)
		return 0;
	if (ft_strcmp(exec_data->cmds_array[0], "env") == 0)
		exit_s = ft_env(1, *env);
	else if (ft_strcmp(exec_data->cmds_array[0], "unset") == 0)
		ft_unset(exec_data->cmds_array, env);
	else if (ft_strcmp(exec_data->cmds_array[0], "cd") == 0)
		me_cd(exec_data->cmds_array, env);
	else if(ft_strcmp(exec_data->cmds_array[0], "echo") == 0)
		my_echo(exec_data->cmds_array);
	else if(ft_strcmp(exec_data->cmds_array[0], "pwd") == 0)
		me_pwd(1, env);
	else if(ft_strcmp(exec_data->cmds_array[0], "exit") == 0)
		mini_exit(exec_data->cmds_array, exit_s);
	else if (ft_strcmp(exec_data->cmds_array[0], "export") == 0)
		export_it(exec_data->cmds_array, env);
	else 
		return 0;
	return exit_s;
}

int is_bult_in(char *arg)
{
	if (ft_strcmp(arg, "env") == 0)
		return 1;
	else if (ft_strcmp(arg, "unset") == 0)
		return 1;
	else if (ft_strcmp(arg, "cd") == 0)
		return 1;
	else if (ft_strcmp(arg, "export") == 0)
		return 1;
	else if (ft_strcmp(arg, "exit") == 0)
		return 1;
	else if (ft_strcmp(arg, "pwd") == 0)
		return 1;
	else if(ft_strcmp(arg, "echo") == 0)
		return 1;
	else
		return 0;
}
