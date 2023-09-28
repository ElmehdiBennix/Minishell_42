/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:05:44 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/28 02:37:34 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*update_env(t_env **env, char *value, char *key)
{
	t_env	*tmp;
	int		fod;

	tmp = *env;
	fod = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			fod = 1;
			if (tmp->value)
				free(tmp->value);
			if (value != NULL) 
				tmp->value = ft_strdup(value);
			tmp = *env;
			return (tmp);
		}
		tmp = tmp->next;
	}
	tmp = *env;
	if (!fod)
		ft_lstadd_back_env(&tmp, ft_lstnew_env(ft_strdup(key), \
			ft_strdup(value)));
	return (tmp);
}
