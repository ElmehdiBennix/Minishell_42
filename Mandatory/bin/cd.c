/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:52:57 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/21 04:33:47 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_cur_path(t_env *env, int flag)
{
	char	*path;
	
	if (flag == 0)
	{
		path = getcwd(NULL, 0);
		env = update_old_pwd(&env, path); 
		free(path);
	}
	else if(flag == 1)
	{
		path = getcwd(NULL, 0);
		env = update_pwd(&env, path);
		free(path);
	}
}

void	me_cd(char **cmd_array, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	get_cur_path(env, 0);
	if (!cmd_array[1]) // protect
	{
		if (chdir(value_by_key(tmp, "HOME")))
			printf("HOME not set\n");
	}
	else
	{
		if (chdir(cmd_array[1]))
			printf("error: cannot find directory\n");
	}
	get_cur_path(env, 1);
}
// cd -
// cd ~
// if someone unseted  HOME delet the node with OLDPWD AS KEY 
// check for leaks