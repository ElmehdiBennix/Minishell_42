/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/14 05:25:02 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	pipe_resources(char *prompt)
{
	int	i;
	unsigned int	pipe;

	i = -1;
	pipe = 0;
	while (prompt[++i])
	{
		if (prompt[i] == '|')
		{
			pipe++;
			if (prompt[++i] && prompt[i] == '|')
			{
				ft_fprintf(2, "le minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
			i--;
		}
	}
	if (pipe >= 550)
	{
		ft_fprintf(2,"le minishell: fork Resource unavailable\n");
		return (2);
	}
	return (0);
}

bool	skip_space_history(char *prompt)
{
	unsigned int	i;

	i = 0;
	while (prompt[i] && ft_iswhite_space(prompt[i]) == 1)
		i++;
	if (prompt[i] == '\0')
		return (1);
	return (0);
}

int	first_index(char *prompt)
{
	if (prompt[0] && (prompt[0] == ')' || prompt[0] == '(' || prompt[0] == '|'))
	{
		ft_fprintf(2,"le minishell: syntax error near unexpected token `%c'\n", prompt[0]);
		return (1);
	}
	return (0);
}

int	last_index(char *prompt)
{
	int		i;
	char	*tokens;

	tokens = "<|>";
	i = ft_strlen(prompt) - 1;
	if (ft_strchr(tokens, prompt[i]))
	{
		ft_fprintf(2,"le minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

bool	open_quote(char *prompt)
{
	int i;
	bool status;

	i = 0;
	status = false;
	while (prompt[i])
	{
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
	if (open_quote(prompt) == 1)
	{
		ft_fprintf(2,"le minishell: syntax error `open quote'\n");
		return (free(prompt), var->err_no = 2, 1); // conti save his
	}
	if (pipe_resources(prompt) != 0)
		return (free(prompt), var->err_no = 2, 1); // conti save his
	return (0); // dont cont
}

static void shell_loop(t_mini_data *var ,char *prompt) // void for now might change it in the future
{
	prompt = ft_strtrim(prompt," ");
	var->tokens = get_tokens(prompt);
	free(prompt);
	// tokenizer(tokens);
}

int main(int ac, char **av , char **env)
{
	(void)env;
	(void)av;
    char *prompt;
    t_mini_data var;

	if (ac == 1)
	{
		while (1)
		{
			prompt = readline("-> le minishit$ "); // should display corrent dir and exit msgs zith colors sigf when cntr + c or sm protect read line and make signales work
			if (shell_history(&var, prompt) == 1) // dosent store tabs empty line or empty spaces stinn needs fa function
				continue;
			shell_loop(&var, prompt);
		}
		return (0);

	}
	return (ft_fprintf(2,"le minishell: this shell does not accept any arguments !!\n"), 127);
}
// leaks and misisng alot of protection in case of a fail



