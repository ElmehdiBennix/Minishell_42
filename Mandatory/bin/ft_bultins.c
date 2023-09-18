/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bultins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:50:58 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/18 02:51:03 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_bultin(_prototype *data, char **arg, t_env **env)
{
	static int exit_s = 0;
	
	if (ft_strcmp(arg[0], "env") == 0)
	{
		printf("AKAKA________-------????\n"); // delete
		exit_s = ft_env(1, *env);
	}
	else if (ft_strcmp(arg[0], "unset") == 0)
		ft_unset(arg, env);
	else if (ft_strcmp(arg[0], "cd") == 0)
	{
		me_cd(arg, env);
	}
	else if(ft_strcmp(arg[0], "echo") == 0)
	{
		printf("AKAKA________-------????\n"); // delete
		my_echo(data, arg, env);
	}
	else if(ft_strcmp(arg[0], "pwd") == 0)
		me_pwd(1, arg,  env);
	else if(ft_strcmp(arg[0], "exit") == 0)
		mini_exit(arg, env, exit_s);
	else if (ft_strcmp(arg[0], "export") == 0)
		export_it(arg, env);
	else 
		return 0;
	return exit_s;
}

int is_bult_in(char *arg)
{
	if (ft_strcmp(arg, "env") == 0)
		return TRUE;
	else if (ft_strcmp(arg, "unset") == 0)
		return TRUE;
	else if (ft_strcmp(arg, "cd") == 0)
		return TRUE;
	else if (ft_strcmp(arg, "export") == 0)
		return TRUE;
	else if (ft_strcmp(arg, "exit") == 0)
		return TRUE;
	else if (ft_strcmp(arg, "pwd") == 0)
		return TRUE;
	else if(ft_strcmp(arg, "echo") == 0)
		return TRUE;
	else
		return 0;
}
