/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:05:44 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/02 16:03:16 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
t_env	*update_pwd(t_env *env, char *pwd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	return(tmp); 
}

t_env	*update_old_pwd(t_env *env, char *oldpwd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			if(tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
		}
		tmp = tmp->next;
	}
	return(tmp); 
}