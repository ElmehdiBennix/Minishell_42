/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 23:32:34 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 23:34:54 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	skip_space_history(char *prompt)
{
	unsigned int	i;

	i = 0;
	while (prompt[i] && ft_iswhite_space(prompt[i]) == TRUE)
		i++;
	if (prompt[i] == '\0')
		return (1);
	return (0);
}

bool	first_index(char *prompt)
{
	unsigned int	i;

	i = 0;
	while (prompt[i] && ft_iswhite_space(prompt[i]) == TRUE)
		i++;
	if (prompt[i] && (prompt[i] == ')' || prompt[i] == '(' || prompt[i] == '|'))
		return (ft_fprintf(2, SYNX_1, prompt[i]), 1);
	return (0);
}

bool	last_index(char *prompt)
{
	unsigned int	i;

	i = ft_strlen(prompt) - 1;
	while (prompt[i] && ft_iswhite_space(prompt[i]) == TRUE)
		i--;
	if (prompt[i] && (prompt[i] == '<' || prompt[i] == '|' || prompt[i] == '>'))
		return (ft_fprintf(2, SYNX_2), 1);
	return (0);
}
