/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 02:37:18 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/06 21:32:09 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

int	get_env(t_env **Henv, char **env)
{
	t_env	*tmp;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (!env)
		return (1);
	while (env[i])
	{
		key = get_key(env[i]);
		value = get_val(env[i]);
		tmp = ft_lstnew_env(key, value);
		if (!Henv)
			Henv = &tmp;
		else
			ft_lstadd_back_env(Henv, tmp);
		i++;
	}
	return (0);
}

char	*get_key(char *line)
{
	char	*key;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && (line[i] != '='))
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (line[i] && (line[i] != '='))
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_val(char *line)
{
	char	*val;
	int		i;
	int		j;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == '=' && line[i + 1] == 0)
		return (ft_strdup(""));
	if (!line[i] || !line[i + 1])
		return (NULL);
	j = i + 1;
	while (line[j])
		j++;
	val = malloc(sizeof(char) * (j - i + 1));
	if (!val)
		return (NULL);
	j = i + 1;
	i = 0;
	while (line[j])
		val[i++] = line[j++];
	val[i] = '\0';
	return (val);
}
