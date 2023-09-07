/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:05:55 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/07 19:07:55 by otaraki          ###   ########.fr       */
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

void	excute_one_cmd(t_token **args, char **contents, t_env **env)
{
	char	*path;
	char	*str;
	char	**splited_path;

	if (!contents[0])
		return ;
	if (ft_bultin((*args), contents, env) == BULT_IN)
		return ;
	else
	{
		path = value_by_key(*env, "PATH");
		if (path == NULL)
			return ; // error handel : PATH NOT FOUND;(to add)
		splited_path = ft_split(path, ':');
		str = check_path(splited_path, contents[0]);
		if (!str)
			return ;// error handel
		int id = fork();
		if (id == 0)
		{
			if ((*args)->fdin != 0)
			{
				if (dup2((*args)->fdin, STDIN_FILENO) < 0)
					return ;
				close((*args)->fdin);
			}
			if ((*args)->fdout != 1)
			{	
				if (dup2((*args)->fdout, STDOUT_FILENO) < 0)
					return ;
				close((*args)->fdout);
			}
			execve(str, contents, get_normal_env(*env));// check case of failure
		}
		if ((*args)->fdin != 0)
			close((*args)->fdin);
		if ((*args)->fdout != 1)
			close((*args)->fdout);
		wait(NULL);
	}
}

void	one_cmd(t_token **data, char **cmds,  t_env **env)
{
	size_t i;
	int status; // close all file descriptors in the parent and child process

	i = 0;
	while(cmds[i])
	{
		if (!ft_strcmp(cmds[i], ">"))
		{
			status = red_open(data, GREAT, cmds[i + 1]);
			free(cmds[i]);
			cmds[i] = NULL;
		}
		else if (!ft_strcmp(cmds[i], "<"))
		{
			status = red_open(data, LESS, cmds[i + 1]);
			free(cmds[i]);
			cmds[i] = NULL;
		}
		else if (!ft_strcmp(cmds[i], ">>"))
		{
			append(&(*data)->fdin, cmds[i + 1]);
			status = red_open(data, APPEND, cmds[i + 1]);
			free(cmds[i]);
			cmds[i] = NULL;
		}
		else if (!ft_strcmp(cmds[i], "<<"))
		{
			here_doc(&(*data)->fdin ,cmds[i + 1]);
			status = red_open(data, HERE_DOC, "/tmp/here_doc");
			free(cmds[i]);
			cmds[i] = NULL;
		}
		if (status < 0)
			exit(0);// check if theere is an error > error handing
		++i;
	}
	excute_one_cmd(data, cmds,  env);
}

void	exceute_it(t_token **data, t_env **env)
{
	t_token *iter;
	int		numb_pipes;

	iter = *data;
	numb_pipes = -1;
	while (iter)
	{
		numb_pipes++;
		iter = iter->forward;// check if theres a | 
	}
	if (numb_pipes == 0)
		one_cmd(data, (*data)->content, env);
	else 
		multi_cmd(data, env, numb_pipes);
}