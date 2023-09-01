/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_back_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:43:50 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/31 23:58:34 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_normal_env(t_env **env)
{
	t_env	*tmp;
	char	*arr;
	char	**envir;
	int		i;
	
	tmp = *env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		++i;	
	}
	envir = malloc(sizeof(char *) * i + 1);
	if (!envir)
		return (NULL);
	tmp = *env;
	i = 0;
	while (tmp)
	{
		arr = ft_strjoin(tmp->key, tmp->value);
		envir[i] = arr;
		free(arr);
		tmp = tmp->next;
	}
	envir[i] = NULL;
	return (envir);
}
