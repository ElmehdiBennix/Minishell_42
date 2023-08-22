/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:51:37 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/22 22:54:15 by ebennix          ###   ########.fr       */
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
// 				ft_fprintf(2, "le minishell: syntax error near unexpected token `|'\n");
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
	while (prompt[i] && ft_iswhite_space(prompt[i]) == 1)
		i++;
	if (prompt[i] == '\0')
		return (1);
	return (0);
}

static bool	first_index(char *prompt)
{
	if (prompt[0] && (prompt[0] == ')' || prompt[0] == '(' || prompt[0] == '|'))
	{
		ft_fprintf(2,"le minishell: syntax error near unexpected token `%c'\n", prompt[0]);
		return (1);
	}
	return (0);
}

static bool	last_index(char *prompt)
{
	int		i;

	i = ft_strlen(prompt) - 1;
	if (prompt[i] == '<' || prompt[i] == '|' || prompt[i] == '>')
	{
		ft_fprintf(2,"le minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

static int	open_quote(char *prompt)
{
	int i;
	bool status;

	i = 0;
	status = false;
	while (prompt[i])
	{
		if (prompt[i] == '|')
		{
			if (prompt[++i] && prompt[i] == '|')
				return (-1);
			i--;
		}
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			char quot = prompt[i];
			status = true;
			i++;
			while (prompt[i] && prompt[i] != quot)
				i++;
			if (prompt[i] == quot)
				status = false;
		}
		i++;
	}
	return (status);
}

bool shell_history(t_mini_data *var, char *prompt)
{
	if (!prompt || prompt[0] == '\0' || skip_space_history(prompt) == 1)
		return (free(prompt),var->err_no = 1, 1); // conti dont save hist
	add_history(prompt);
	if (first_index(prompt) == 1 || last_index(prompt) == 1)
		return (free(prompt), var->err_no = 2, 1); // conti save hist
	int error = open_quote(prompt);
	if (error == 1)
	{
		ft_fprintf(2,"le minishell: syntax error `open quote'\n");
		return (free(prompt), var->err_no = 2, 1); // conti save his
	}
	else if (error == -1)
	{
		ft_fprintf(2, "le minishell: syntax error near unexpected token `|'\n");
		return (free(prompt), var->err_no = 2, 1); // conti save his
	}
	// if (pipe_resources(prompt) != 0) // pipes is useless
	// 	return (free(prompt), var->err_no = 2, 1); // conti save his
	return (0); // dont cont
}