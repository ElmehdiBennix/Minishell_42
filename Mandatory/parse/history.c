/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:51:37 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/24 03:17:22 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	pipe_resources(char *prompt) // bad idea
// {
// 	int	i;
// 	unsigned int	pipe;

// 	i = -1;
// 	pipe = 0;
// 	while (prompt[++i])
// 	{
// 		if (prompt[i] == '|')
// 		{
// 			pipe++;
// 			if (prompt[++i] && prompt[i] == '|')
// 			{
// 				ft_fprintf(2,"le minishell: syntax error near unexpected token `|'\n");
// 				return (1);
// 			}
// 			i--;
// 		}
// 	}
// 	if (pipe >= 550)
// 	{
// 		ft_fprintf(2,"le minishell: fork Resource unavailable\n");
// 		return (2);
// 	}
// 	return (0);
// }

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
	int i = 0;

	while (prompt[i] && ft_iswhite_space(prompt[i]) == TRUE)
		i++;
	if (prompt[i] && (prompt[i] == ')' || prompt[i] == '(' || prompt[i] == '|'))
	{
		ft_fprintf(2, "le minishell: syntax error near unexpected token `%c'\n",prompt[i]);
		return (1);
	}
	return (0);
}

static bool	last_index(char *prompt)
{
	int	i;

	i = ft_strlen(prompt) - 1;
	while (prompt[i] && ft_iswhite_space(prompt[i]) == TRUE)
		i--;
	if (prompt[i] && (prompt[i] == '<' || prompt[i] == '|' || prompt[i] == '>')) // to check later
	{
		ft_fprintf(2,"le minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

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
		if (prompt[i] == '|')
		{
			if (prompt[++i] && prompt[i] == '|')
				return (-1);
			i--;
			command_table++;
		}
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			quot = prompt[i];
			status = TRUE;
			i++;
			while (prompt[i] && prompt[i] != quot)
				i++;
			if (prompt[i] == quot)
				status = FALSE;
		}
		i++;
	}
	var->nodes = command_table;
	return (status);
}

bool	shell_history(t_mini_data *var, char *prompt)
{
	if (!prompt || prompt[0] == '\0' || skip_space_history(prompt) == TRUE)
		return (free(prompt), var->err_no = 1, 1); // conti dont save hist
	add_history(prompt);
	if (first_index(prompt) == TRUE || last_index(prompt) == TRUE)
		return (free(prompt), var->err_no = 2, 1); // conti save hist
	int err = open_quote(var , prompt);
	if (err == 1)
	{
		ft_fprintf(2, "le minishell: syntax error `open quote'\n");
		return (free(prompt), var->err_no = 2, 1); // conti save hist
	}
	else if (err == -1)
	{
		ft_fprintf(2, "le minishell: syntax error near unexpected token `|'\n");
		return (free(prompt), var->err_no = 2, 1); // conti save hist
	}
	// if (pipe_resources(prompt) != 0) // pipes is useless
	// 	return (free(prompt), var->err_no = 2, 1); // conti save his
	return (0); // dont conti
}
