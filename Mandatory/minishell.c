/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/22 23:26:02 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static void	parse_loop(t_mini_data *var, char *prompt) // void for now might change it in the future
{
	prompt = ft_strtrim(prompt, " ");
	var->tokens = get_tokens(prompt);
	free(prompt);
	tokenizer(var->tokens);

}

int	main(int ac, char **av, char **env)
{
	char		*prompt;
	t_mini_data	var;

	(void)env;
	(void)av;
	if (ac == 1)
	{
		while (1)
		{
			// prompt = prompt_generator(&var);
			// signals --
			prompt = readline(GREEN "-> le minishit" DEFAULT "$ "); // should display corrent dir and exit msgs zith colors sigf when cntr+ c or sm protect read line and make signales work
			if (shell_history(&var, prompt) == 1) // dosent store tabs empty line or empty spaces stinn needs fa function
				continue ;
			parse_loop(&var, prompt);
			// exec loop
		}
		return (0);
	}
	return (ft_fprintf(2,"le minishell: this shell does not accept any arguments !!\n"),127);
}
// leaks and misisng alot of protection in case of a fail
