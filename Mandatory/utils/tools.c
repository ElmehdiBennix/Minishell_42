/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 23:53:29 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/13 23:53:34 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	**get_path(char **env)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**path_spl;

	i = 0;
	path = NULL;
	while (env[i] && path == NULL)
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	if (path == NULL)
		return (NULL);
	path_spl = ft_split(path + 5, ':');
	i = 0;
	while (path_spl[i])
	{
		tmp = ft_strjoin(path_spl[i], "/");
		// free(path_spl[i]);
		path_spl[i] = tmp;
		i++;
	}
	return (path_spl);
}
char *get_pwds(char **env , char *key ,size_t len)
{
	int		i;
	char	*pwd;
	char	*pwd_dup;

	i = 0;
	pwd = NULL;
	while (env[i] && pwd == NULL)
	{
		pwd = ft_strnstr(env[i], key, len);
		i++;
	}
	if (pwd == NULL)
		return (NULL);
	pwd_dup = ft_strdup(pwd + len);
	return (pwd_dup);
}
char **get_env(char **env) // add it as a linked list with key value makes job easier in future
{
	int i;
	char **env_ptr;

	i = 0;
    while(env[i])
		i++;
	env_ptr = ft_calloc(i + 1,sizeof(char *));
	i = 0;
    while(env[i])
    {
        env_ptr[i] = ft_strdup(env[i]);
        i++;
    }
    return(env_ptr);
}
