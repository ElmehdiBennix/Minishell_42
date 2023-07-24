/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/24 04:37:28 by ebennix          ###   ########.fr       */
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
        printf("%s\n",path_spl[i]);
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

void shell_loop(char *var)
{
    char *prompt;

    while (1)
    {
        prompt = readline("le minishit : "); // should display corrent dir and exit msgs zith colors
        ft_fprintf(1,"%s\n",prompt);
        
        // parsing(prompt);
    }
}

char **get_env(char **env)
{
	int i;
	char **env_ptr;

	i = 0;
    while(env[i])
		i++;
	env_ptr = calloc(i + 1,sizeof(char *));
	i = 0;
    while(env[i])
    {
        env_ptr[i] = strdup(env[i]);
        i++;
    }
    return(env_ptr);
}

int main(int ac, char **av , char **env)
{
    // extern char **environ;
    // t_mini_data var;

    // char **p = get_env(env);
	// while(*p)
	// {
	// 	printf("%s\n",*p);
	// 	p++;
	// }
    // printf("%s\n",get_pwds(env,"PWD=",4));
    // printf("%s\n",get_pwds(env,"OLDPWD=",7));
    // get_path(env);

    // shell_loop(&var);
}

// leaks and misisng alot of protection in case of a fail