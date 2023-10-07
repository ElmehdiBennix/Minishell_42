/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:05:55 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 22:37:39 by otaraki          ###   ########.fr       */
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

int	exec_cmd(char **contents, t_env **env)
{
	char	*path;
	char	**splited_path;
	char	*str;

	path = value_by_key(*env, "PATH");
	if (path == NULL)
		return (ft_fprintf(2, "%s: No such file or directory\n", contents[0]),
			2);
	splited_path = ft_split(path, ':');
	str = check_path(splited_path, contents[0]);
	free2d(splited_path);
	if (!str)
		return (ft_fprintf(2, "%s: command not found\n", contents[0]), 2);
	if (execve(str, contents, get_normal_env(*env)) < 0)
		return (perror(""), free(str), 2);
	return (1);
}

int	excute_one_cmd(char **contents, t_env **env)
{
	int	ret;

	ret = 0;
	if (!contents)
		return (2);
	if (ft_strchr(contents[0], ' '))
		contents = ft_split(contents[0], ' ');
	if (ft_strchr(contents[0], '/'))
	{
		if (access(contents[0], X_OK) < 0)
			return (ft_fprintf(2, "%s: No such file or directory\n",
					contents[0]), 2);
		else if (execve(contents[0], contents, get_normal_env(*env)) < 0)
			return (perror(""), 2);
	}
	else
		ret = exec_cmd(contents, env);
	return (ret);
}

void	dub_for_bultins(t_command_table *exec_data)
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
}

int	one_cmd(t_command_table *exec_data, t_env **env)
{
	int		save;
	int		out;
	char	**cmd;

	cmd = exec_data->cmds_array;
	out = dup(1);
	save = 0;
	if (cmd == NULL || !cmd[0])
		return (2);
	if (is_bult_in(cmd[0]) == 1)
	{
		dub_for_bultins(exec_data);
		save = ft_bultin(exec_data, env);
		dup2(out, STDOUT_FILENO);
		if (save == -1)
			return (3);
	}
	else if (multi_cmd(exec_data, env) == 1)
		return (g_err = 127, 2);
	close(out);
	return (0);
}
