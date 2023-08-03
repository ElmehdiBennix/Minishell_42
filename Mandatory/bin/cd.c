/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:52:57 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/03 11:16:17 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_cur_path(t_env *env, int flg)
{
	char	*path;
	
	if (flg == 0)
	{
		path = getcwd(NULL, 0);
		env = update_old_pwd(env, path);
		free(path);
	}
	else if(flg == 1)
	{
		path = getcwd(NULL, 0);
		env = update_pwd(env, path);
		free(path);
	}
}

void	me_cd(char **av, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	get_cur_path(env, 0);
	if (!av[1])
	{
		if (chdir(value_by_key(tmp, "HOME")))
			printf("HOME not set\n");
	}
	else
	{
		if (chdir(av[1]))
			printf("error: cannot find directory");
	}
	get_cur_path(env, 1);
}
// cd -
// if someone unseted  HOME delet the node with OLDPWD AS KEY 
// check for leaks