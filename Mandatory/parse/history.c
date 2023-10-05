/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:51:37 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 22:41:07 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	skip_space_history(char *prompt)
{
	unsigned int	i;

	i = 0;
	while (prompt[i] && ft_iswhite_space(prompt[i]) == TRUE)
		i++;
	if (prompt[i] == '\0')
		return (1);
	return (0);
}

static bool	first_index(char *prompt)
{
	unsigned int	i;

	i = 0;
	while (prompt[i] && ft_iswhite_space(prompt[i]) == TRUE)
		i++;
	if (prompt[i] && (prompt[i] == ')' || prompt[i] == '(' || prompt[i] == '|'))
		return (ft_fprintf(2, SYNX_1, prompt[i]), 1);
	return (0);
}

static bool	last_index(char *prompt)
{
	unsigned int	i;

	i = ft_strlen(prompt) - 1;
	while (prompt[i] && ft_iswhite_space(prompt[i]) == TRUE)
		i--;
	if (prompt[i] && (prompt[i] == '<' || prompt[i] == '|' || prompt[i] == '>'))
		return (ft_fprintf(2, SYNX_2), 1);
	return (0);
}

// static int open_quote(t_mini_data *var, char *prompt)
// {
//     int i = 0;
//     bool status = false;
//     char quot;
//     int command_table = 1;

//     while (prompt[i])
//     {
//         if (prompt[i] == '|')
//         {
//             if (prompt[++i] &&prompt[++i] == '|')
//                 return -1;
//             i--;
//             command_table++;
//         }
//         else if ((prompt[i] == 34 || prompt[i] == 39) && !status)
//         {
//             quot = prompt[i];
//             status = true;
//         }
//         else if (prompt[i] == quot)
//             status = false;
//         i++;
//     }

//     var->nodes = command_table;
//     return status;
// }

static int	open_quote(t_mini_data *var, char *prompt)
{
	int		i;
	bool	status;
	char	quot;
	int		command_table;

	command_table = 1;
	i = 0;
	status = FALSE;
	while (prompt[i])
	{
		if (prompt[i] && prompt[i] == '|')
		{
			if (prompt[++i] && prompt[i] == '|')
				return (-1);
			i--;
			command_table++;
		}
		if (prompt[i] && (prompt[i] == 34 || prompt[i] == 39))
		{
			quot = prompt[i];
			status = TRUE;
			i++;
			while (prompt[i] && prompt[i] != quot)
				i++;
			if (prompt[i] == quot)
				status = FALSE;
		}
		if (prompt[i] == '\0')
			break ;
		i++;
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
	err = open_quote(var, prompt);
	if (err == 1)
		return (ft_fprintf(2, SYNX_3), free(prompt), var->err_no = 258, 1);
	else if (err == -1)
		return (ft_fprintf(2, SYNX_4), free(prompt), var->err_no = 258, 1);
	if (var->nodes >= 400)
		return (ft_fprintf(2, SYNX_5), free(prompt), var->err_no = 258, 1);
	return (0);
}
