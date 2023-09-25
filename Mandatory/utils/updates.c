/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:05:44 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/26 00:32:53 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*update_pwd(t_env **env, char *pwd)
{
	t_env	*tmp;
	int		fod;

	tmp = *env;
	fod = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			fod = 1;
			if (tmp->value)
				free(tmp->value);
			if(pwd != NULL) 
				tmp->value = ft_strdup(pwd);
			tmp  = *env;
			return (tmp);
		}
		tmp = tmp->next;
	}
	tmp  = *env;
	if (!fod)
		ft_lstadd_back_env(&tmp, ft_lstnew_env(ft_strdup("PWD"), ft_strdup(pwd)));
	return(tmp);
}

t_env	*update_old_pwd(t_env **env, char *oldpwd)
{
	t_env	*tmp;
	int		fod;
	
	tmp = *env;
	fod = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			if( tmp->value)
				free(tmp->value);
			if (oldpwd != NULL)
				tmp->value = ft_strdup(oldpwd);
			tmp  = *env;
			return (tmp); ;
		}
		tmp = tmp->next;
	}
	tmp  = *env;
	if (!fod)
		ft_lstadd_back_env(&tmp, ft_lstnew_env(ft_strdup("OLDPWD"), ft_strdup(oldpwd))); // leaks
	return(tmp);
}
