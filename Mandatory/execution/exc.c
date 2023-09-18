/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:05:55 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/18 02:55:15 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft__strjoin(char const *s1, char const *s2)
{
	int	i;
	int	j;
	int	len_s1;
	int	len_s2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len_s1)
		str[j++] = s1[i++];
	i = 0;
	while (i < len_s2)
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char *check_path(char **s_path, char *cmd)
{
	int i;
	char *j_cmd;
	char *j_path;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	j_cmd = ft__strjoin("/", cmd);
	if (!j_cmd)
		return (NULL);
	while (s_path[i])
	{
		j_path = ft__strjoin(s_path[i], j_cmd);
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

void excute_one_cmd(_prototype **args, char **contents, t_env **env)
{
	char *path;
	char *str;
	char **splited_path;

	(void)args;
	if (!contents[0])
		return;
	else
	{
		path = value_by_key(*env, "PATH");
		if (path == NULL)
			return; // error handel : PATH NOT FOUND;(to add)
		splited_path = ft_split(path, ':');
		str = check_path(splited_path, contents[0]);
		if (!str)
			return;									 // error handel
		execve(str, contents, get_normal_env(*env)); // check case of failure 
	}
}

void one_cmd(_prototype **cmds, char **args, t_env **env)
{
	// int save = 0;
	int out;

	if (!args[0])
		return ;
	out = dup(1);
	if (is_bult_in(args[0]) == TRUE)
	{
		if ((*cmds)->fdin != 0)
		{
			dup2((*cmds)->fdin, STDIN_FILENO);
			close((*cmds)->fdin);
		}

		if ((*cmds)->fdout != 1)
		{
			dup2((*cmds)->fdout, STDOUT_FILENO);
			close((*cmds)->fdout);
		}
		// save = ft_bultin(*cmds, args, env);
		ft_bultin(*cmds, args, env);
		dup2(out, STDOUT_FILENO);
	}
	else
		multi_cmd(cmds, env);
}
