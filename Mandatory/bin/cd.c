/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:52:57 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/25 03:57:57 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_old_current(t_env *env, char *path,  int flag)
{	
	if (flag == 0)
		env = update_old_pwd(&env, path);
	else if(flag == 1)
		env = update_pwd(&env, path);
}

void	me_cd(char **cmd_array, t_env **env)
{
	t_env	*tmp;
	char	*path;

	tmp = *env;
	path = getcwd(NULL, 0);
	if (!cmd_array[1])
	{
		if (chdir(value_by_key(tmp, "HOME")))
			printf("HOME not set\n");
		else
			update_old_current(*env, path, 0);
	}
	else
	{
		if (!ft_strcmp(cmd_array[1], "-"))	
		{
			tmp = *env;
			if (chdir(value_by_key(tmp, "OLDPWD")))
				printf("error: cannot find directory\n");
		}
		else if (chdir(cmd_array[1]))
			printf("error: cannot find directory\n");
		else
			update_old_current(*env, path, 0);
	}
	free(path);
	path = getcwd(NULL, 0);
	update_old_current(*env, path, 1);
	// me_pwd(1, env);
	free(path);
}
// if someone unseted  HOME delet the node with OLDPWD AS KEY 
// check for leaks