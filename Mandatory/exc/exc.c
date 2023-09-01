/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:05:55 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/01 01:38:04 by otaraki          ###   ########.fr       */
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

void	excute_one_cmd(t_token **args, t_env **env)
{
	char	*path;
	char	**splited_path;

	path = value_by_key(*env, "PATH");
	if(path == NULL)
		return ;// error handel : PATH NOT FOUND;(to add)
	splited_path = ft_split(path, ':');
	int id = fork();
	if (id == 0)
	{
		execve(check_path(splited_path, (*args)->content[0]),
			(*args)->content, get_normal_env(env));// check case of failure
	}
	wait(NULL);
}
void	one_cmd(t_token **data, t_env **env)
{
	size_t i;
	int status; // close all file descriptors in the parent and child process

	i = 0;
	while((*data)->content[i])
	{
		if (!ft_strcmp((*data)->content[i], ">"))
		{
			status = red_open(GREAT, (*data)->content[i + 1]); 
			(*data)->content[i] = NULL;
		}
		else if (!ft_strcmp((*data)->content[i], "<"))
		{
			status = red_open(LESS, (*data)->content[i + 1]);
			(*data)->content[i] = NULL;
		}
		else if (!ft_strcmp((*data)->content[i], ">>"))
		{
			status = red_open(APPEND, (*data)->content[i + 1]);
			(*data)->content[i] = NULL;
		}
		// else if (!ft_strcmp((*data)->content[i], "<<"))
		// {
		// 	// status = here_doc((*data)->content[i + 1]);
		// }
		// if (status < 0)
		// 	exit(0);
		++i;
	}
	excute_one_cmd(data, env);
}

void	exceute_it(t_token **data, t_env **env)
{
	t_token *iter;
	int		numb_pipes;
	// int		**fd;

	iter = *data;
	numb_pipes = -1;
	while (iter)
	{
		numb_pipes++;
		iter = iter->forward;// I am gonna check if theres a | 
	}
	if (numb_pipes == 0)
	{
		one_cmd(data, env);
	}
}