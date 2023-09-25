/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:52:57 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/25 23:27:56 by otaraki          ###   ########.fr       */
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
	int		flg;

	tmp = *env;
	path = getcwd(NULL, 0);
	flg = 0;
	if (!path)
		return(perror("getcwd"));
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
			flg = 1;
		}
		else if (chdir(cmd_array[1]))
			printf("error: cannot find directory\n");
		else
			update_old_current(*env, path, 0);
	}
	free(path);
	path = getcwd(NULL, 0);
	if (!path)
		return (perror("getcwd: "));
	update_old_current(*env, path, 1);
	if (flg)
		me_pwd(1, env);
	free(path);
}
// check for leaks