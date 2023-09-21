/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:05:55 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/21 07:07:23 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *check_path(char **s_path, char *cmd)
{
	int i;
	char *j_cmd;
	char *j_path;

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

int excute_one_cmd(char **contents, t_env *env)
{
	char *path;
	char *str;
	char **splited_path;

	if (!contents[0])// don't check about it, should be handled by the parser!
		return (2);
	else
	{
		// if (access(str, F_OK) == -1)
		// 	return(ft_putstr_fd("PERMISSION DENIED ÁA WLD L9AHBA\n", 2), 2);
		path = value_by_key(env, "PATH");
		if (path == NULL)
			return (printf("%s: No such file or directory\n", contents[0]), 2);
		splited_path = ft_split(path, ':');// check for NULL if returned
		str = check_path(splited_path, contents[0]);
		if (!str)
			return (printf("Error :command not found\n"), 2);
		free2d(splited_path);
		if (execve(str, contents, get_normal_env(env)) < 0)
			return (perror(""), 2);
		return 1;
	}
}

void 	one_cmd(t_command_table *exec_data, t_env *env)
{
	int save;
	int out;

	// args == commands array
	if (exec_data->cmds_array == NULL)
		return ;
	out = dup(1);
	if (is_bult_in(exec_data->cmds_array[0]) == 1)
	{
		// if (exec_data->fdin != 0)
		// {
		// 	dup2(exec_data->fdin, STDIN_FILENO);
		// 	close(exec_data->fdin);
		// }
		// if (exec_data->fdout != 1)
		// {
		// 	dup2(exec_data->fdout, STDOUT_FILENO);
		// 	close(exec_data->fdout);
		// }
		save = ft_bultin(exec_data, env);
		// dup2(out, STDOUT_FILENO);
	}
	else
		multi_cmd(exec_data, env);
}

// void exceute_it(t_token **data, t_env **env)
// {
// 	t_token		*iter;
// 	int			numb_pipes;

// 	iter = *data;
// 	numb_pipes = -1;
// 	while (iter)
// 	{
// 		open_red(&iter, iter->content);
// 		numb_pipes++;
// 		iter = iter->forward;
// 	}
// 	if (numb_pipes == 0)
// 		one_cmd(data, (*data)->content, env);
// 	else
// 		multi_cmd(data, env);
// }
