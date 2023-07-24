/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/24 02:05:42 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"


char	**parsing(char **env)
{
	int		i;
	char	*tmp;
	char	**splitz;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i] && path == NULL)
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	if (path == NULL)
		return (NULL);
	splitz = ft_split(path + 5, ':');
	i = 0;
	while (splitz[i])
	{
		tmp = ft_strjoin(splitz[i], "/");
		free(splitz[i]);
		splitz[i] = tmp;
		i++;
	}
	return (splitz);
}


void shell_loop()
{
    char *prompt;

    while (1)
    {
        prompt = readline("le minishit : "); // should display corrent dir and exit msgs zith colors
        // ft_fprintf(1,"%s\n",prompt);
        // parsing(prompt);
        // this is it le 
        
    }
}

int main(void)
{
    extern char **environ;
    t_mini_data var;

    get_env();
    get_pwds();
    get_path();
    shell_loop();
}