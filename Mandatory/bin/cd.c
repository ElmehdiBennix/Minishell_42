/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:52:57 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/06 19:35:15 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_old_current(t_env *env, char *path, int flag)
{
	if (flag == 0)
		env = update_env(&env, path, "OLDPWD");
	else if (flag == 1)
		env = update_env(&env, path, "PWD");
	if (path)
		free(path);
}

int	dr_chdir(char *dir_name, char *msg_err, char *path, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (chdir(value_by_key(tmp, dir_name)))
		return (ft_fprintf(2, "%s\n", msg_err) - 1);
	else
		update_old_current(*env, path, 0);
	return (0);
}

int	change_dr(char **cmd_arr, t_env **env, char *path, int *flg)
{
	int	ret;

	ret = 0;
	if (!cmd_arr[1])
		ret = dr_chdir("HOME", "cd: cannot find directory", path, env);
	else if (!ft_strcmp(cmd_arr[1], "-"))
	{
		ret = dr_chdir("OLDPWD", "cd: cannot find directory", path, env);
		(*flg) = 1;
	}
	else if (chdir(cmd_arr[1]))
	{
		if (access(cmd_arr[1], F_OK) == 0)
			return (ft_fprintf(2, "cd: Permission denied\n"), -1);
		else
			return (ft_fprintf(2, "cd: cannot find directory\n"), -1);
	}
	else
		update_old_current(*env, path, 0);
	return (ret);
}

int	me_cd(char **cmd_array, t_env **env)
{
	char	*path;
	int		flg;
	int		ret;

	path = getcwd(NULL, 0);
	flg = 0;
	if (!path)
	{
		chdir(cmd_array[1]);
		return (perror("getcwd"), -1);
	}
	ret = change_dr(cmd_array, env, path, &flg);
	path = getcwd(NULL, 0);
	if (!path)
		return (perror("getcwd: "), -1);
	update_old_current(*env, path, 1);
	if (flg)
		me_pwd(1, env);
	return (ret);
}
