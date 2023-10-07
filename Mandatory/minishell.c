/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/07 22:40:23 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static void	exec_loop(t_mini_data *var)
{
	open_red_exec(var);
	if (var->nodes == 1)
		one_cmd_exec(var);
	else
		multi_cmd_exec(var);
	close_red_exec(var);
	unlink_opened_files();
}

static bool	parse_loop(t_mini_data *var, char *prompt)
{
	char	*prompty;

	prompty = prompt;
	prompt = ft_strtrim(prompty, " ");
	free(prompty);
	if (token_catcher(prompt, var) == TRUE)
		return (tok_free(var->tokens, 1), g_err = 258, 1);
	if (parser(var) == TRUE)
		return (tok_free(var->tokens, 1), g_err = 258, 1);
	if (expander(var) == TRUE)
		return (tok_free(var->tokens, 1), g_err = 258, 1);
	if (allocate_groups(var) == TRUE)
		return (cmd_free(var->exec_data, 1), tok_free(var->tokens, 1),
			g_err = 258, 1);
	if (linker(var) == TRUE)
		return (cmd_free(var->exec_data, 1), g_err = 258, 1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*prompt;
	char		*tmp;
	t_mini_data	var;

	(void)av;
	g_err = 0;
	ft_bzero(&var, sizeof(var));
	get_env(&var.env_var, env);
	tmp = ft_itoa(ft_atoi(value_by_key(var.env_var, "SHLVL")) + 1);
	var.env_var = update_env(&var.env_var, tmp, "SHLVL");
	free(tmp);
	if (ac == 1)
	{
		while (1)
		{
			rl_catch_signals = 0;
			var.tokens = NULL;
			var.exec_data = NULL;
			prompt = NULL;
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, signal_handler);
			tmp = prompt_generator();
			prompt = readline(tmp);
			free(tmp);
			if (shell_history(&var, prompt) == TRUE)
				continue ;
			if (parse_loop(&var, prompt) == TRUE)
				continue ;
			exec_loop(&var);
			cmd_free(var.exec_data, 1);
		}
	}
	return (ft_fprintf(2, SYNX_0), 127);
}
