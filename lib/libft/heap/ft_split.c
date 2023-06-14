/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:52:56 by ebennix           #+#    #+#             */
/*   Updated: 2023/05/09 21:15:20 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

static	int	word_counter(char *str, char delim)
{
	int	word;

	word = 0;
	while (*str)
	{
		while (*str != '\0' && *str == delim)
			str++;
		if (*str != '\0' && *str != delim)
		{
			word++;
			while (*str != '\0' && *str != delim)
				str++;
		}
	}
	return (word);
}

static	char	*word_malloc(char *str, char delim)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != delim)
		i++;
	word = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != delim)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char delim)
{
	char	**tab;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	tab = (char **)ft_calloc((word_counter(str, delim) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	while (*str)
	{
		while (*str != '\0' && *str == delim)
			str++;
		if (*str != '\0' && *str != delim)
		{
			tab[i] = word_malloc(str, delim);
			if (tab[i] == NULL)
				return (free2d(tab));
			i++;
			while (*str != '\0' && *str != delim)
				str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
