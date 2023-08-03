/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bultins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:50:58 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/03 11:04:10 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_bultin(char **arg, t_env *env)
{
	if (ft_strcmp(arg[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp(arg[0], "unset") == 0)
		ft_unset(arg, env);
	else if (ft_strcmp(arg[0], "cd") == 0)
		me_cd(arg, env);
	else if(ft_strcmp(arg[0], "echo") == 0)
		my_echo(arg, env);
	else if(ft_strcmp(arg[0], "pwd") == 0)
		me_pwd(arg, env);
}