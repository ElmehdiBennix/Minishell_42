/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:11 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/04 22:29:05 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(int fd, char **av, t_env *env)
{
	if (av[1])
	{
		ft_fprintf(2, "env: %s: No such file or directory\n", av[1]);
		return (-1);
	}
	while (env)
	{
		if (env->value)
			ft_fprintf(fd,"%s=%s\n",env->key,env->value);
		env = env->next;
	}
	return (0);
}
