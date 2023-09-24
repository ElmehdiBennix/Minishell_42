/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:52:57 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/24 00:42:45 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = -1;
	j = -1;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	// free (s1);
	return (str);
}
