/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:39:43 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/05 00:04:10 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*value_by_key(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*key_by_value(t_env *env, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, value) == 0)
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_key_plus(char *line)
{
	char	*key;
	int		i;

	i = 0;
	if (line == NULL)
		return (NULL);
	while (line[i] && (line[i] != '=' && line[i] != '+'))
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (line[i] && (line[i] != '=' && line[i] != '+'))
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}
