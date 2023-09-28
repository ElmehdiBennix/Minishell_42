/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:05:55 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/28 01:52:32 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_path(char **s_path, char *cmd)
{
	int		i;
	char	*j_cmd;
	char	*j_path;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	j_cmd = ft_strjoin("/", cmd);
	if (!j_cmd)
		return (NULL);
	while (s_path[i])
	{
		j_path = ft_strjoin(s_path[i], j_cmd);
		if (access(j_path, X_OK) == 0)
		{
			free(j_cmd);
			return (j_path);
		}
		free(j_path);
		i++;
	}
	free(j_cmd);
	return (NULL);
}

int	excute_one_cmd(char **contents, t_env **env)
{
	char	*path;
	char	*str;
	char	**splited_path;

	if (ft_strchr(contents[0], '/'))
	{
		if (access(contents[0], X_OK) < 0)
			return (printf("%s: No such file or directory\n", contents[0]), 2);
		else
		{
			if (execve(contents[0], contents, get_normal_env(*env)) < 0)
				return (perror(""), 2);
		}
	}
	else
	{
		path = value_by_key(*env, "PATH");
		if (path == NULL)
			return (printf("%s: No such file or directory\n", contents[0]), 2);
		splited_path = ft_split(path, ':');
		str = check_path(splited_path, contents[0]);
		if (!str)
			return (printf("%s: command not found\n", contents[0]), 2);
		free2d(splited_path);
		if (execve(str, contents, get_normal_env(*env)) < 0)
			return (perror(""), 2);
		return (1);
	}
	return (1);
}

int	one_cmd(t_command_table *exec_data, t_env **env)
{
	int	save;
	int	out;

	if (exec_data->cmds_array == NULL || !exec_data->cmds_array[0])
		return (2);
	out = dup(1);
	save = 0;
	if (is_bult_in(exec_data->cmds_array[0]) == 1)
	{
		if (exec_data->fdin != 0)
		{
			dup2(exec_data->fdin, STDIN_FILENO);
			close(exec_data->fdin);
		}
		if (exec_data->fdout != 1)
		{
			dup2(exec_data->fdout, STDOUT_FILENO);
			close(exec_data->fdout);
		}
		save = ft_bultin(exec_data, env);
		dup2(out, STDOUT_FILENO);
	}
	else
		multi_cmd(exec_data, env);
	close(out);
	return (0);
}
