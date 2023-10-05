/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:51:37 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 23:32:50 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int open_quot(char *prompt, int *i)
{
	int status;
	char quot;

	quot = prompt[*i];
	status = TRUE;
	(*i)++;
	while (prompt[*i] && prompt[*i] != quot)
		(*i)++;
	if (prompt[*i] == quot)
		status = FALSE;
	return (status);
}

static int	pipe_quot(t_mini_data *var, char *prompt)
{
	int		i;
	bool	status;
	int		command_table;

	command_table = 1;
	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] && prompt[i] == '|')
		{
			if (prompt[++i] && prompt[i] == '|')
				return (-1);
			i--;
			command_table++;
		}
		if (prompt[i] && (prompt[i] == 34 || prompt[i] == 39))
			status = open_quot(prompt, &i);
		if (prompt[i] == '\0')
			break ;
	}
	var->nodes = command_table;
	return (status);
}

bool	shell_history(t_mini_data *var, char *prompt)
{
	int	err;

	if (!prompt)
		return (ft_fprintf(1, "exit"), exit(0), 1);
	if (prompt[0] == '\0' || skip_space_history(prompt) == TRUE)
		return (free(prompt), 1);
	add_history(prompt);
	if (first_index(prompt) == TRUE || last_index(prompt) == TRUE)
		return (free(prompt), var->err_no = 258, 1);
	err = pipe_quot(var, prompt);
	if (err == 1)
		return (ft_fprintf(2, SYNX_3), free(prompt), var->err_no = 258, 1);
	else if (err == -1)
		return (ft_fprintf(2, SYNX_4), free(prompt), var->err_no = 258, 1);
	if (var->nodes >= 400)
		return (ft_fprintf(2, SYNX_5), free(prompt), var->err_no = 258, 1);
	return (0);
}
