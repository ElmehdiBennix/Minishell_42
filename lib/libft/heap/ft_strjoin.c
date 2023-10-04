/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:11:13 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/04 00:47:04 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;
	int	flag[2];

	i = -1;
	j = -1;
	flag[0] = 0;
	flag[1] = 0;
	if (!s1)
	{
		s1 = ft_strdup("");
		flag[0] = 1;
	}
	if (!s2)
	{
		s2 = ft_strdup("");
		flag[1] = 1;
	}
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
	{
		if(flag[0] == 1)
			free(s1);
		if(flag[1] == 1)
			free(s2);
		return (NULL);
	}
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	if(flag[0] == 1)
		free(s1);
	if(flag[1] == 1)
		free(s2);
	return (str);
}
