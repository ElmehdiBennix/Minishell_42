/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:52:57 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/02 12:26:01 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	me_cd(char **av, t_env *env)
{
	t_env *tmp;
	int i;
	char *path;
	char **s_path;

	tmp = env;
	path = getcwd(NULL, 0);
	printf("Path %s\n", path);
	if (!av[1])
	{
		if (chdir(value_by_key(tmp, "HOME")))
			printf("HOME not set");
	}
	else
	{
		if (av[1][0] == '/')
		{
			if (chdir(av[1]))
				printf("error: cannot find directory");
		}
		else
		{
			s_path = ft_split(av[1], '/');
			i = 0;
			while (s_path[i])
			{
				if (chdir(s_path[i]) != 0)
					printf("couldn't find it OUUUUPSSY\n");
				i++;
			}
		}
	}
	free(path);
	path = getcwd(NULL, 0);
	printf("Path %s\n", path);
	///////////////////
}