/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_back_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:43:50 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/06 20:08:59 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc((len_s1 + len_s2 + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len_s1)
		str[j++] = s1[i++];
	str[j++] = '=';
	i = 0;
	while (i < len_s2)
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

int	ft_size_list(t_env *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		++i;
	}
	return (i);
}

char	**get_normal_env(t_env *env)
{
	t_env	*tmp;
	char	*arr;
	char	**envir;
	int		i;

	if (!env)
		return (NULL);
	tmp = env;
	i = ft_size_list(tmp);
	envir = malloc(sizeof(char *) * (i + 1));
	if (!envir)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		arr = ft_strjoin_env(tmp->key, tmp->value);
		envir[i] = arr;
		tmp = tmp->next;
		i++;
	}
	envir[i] = NULL;
	return (envir);
}
