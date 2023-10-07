/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/06 23:07:06 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	one_cmd_exec(t_mini_data *var)
{
	t_command_table	*cmd;
	int				ret;

	cmd = var->exec_data;
	ret = one_cmd(cmd, &var->env_var);
	if (cmd->cmds_array[0] && ret == 2)
	{
		if (g_err == 0)
			g_err = 127;
	}
	else if (ret == 3)
		g_err = 1;
	else
		g_err = 0;
}

void	multi_cmd_exec(t_mini_data *var)
{
	t_command_table	*m_cmd;

	m_cmd = var->exec_data;
	while (m_cmd && m_cmd->cmds_array == NULL)
	{
		var->nodes--;
		m_cmd = m_cmd->forward;
	}
	if (var->nodes)
	{
		if ((multi_cmd(m_cmd, &var->env_var)) == 1)
		{
			if (!g_err)
				g_err = 127;
		}
		else
			g_err = 0;
	}
}
void	open_red_exec(t_mini_data *var)
{
	t_command_table	*data_iter;
	int				return_type;

	return_type = 0;
	data_iter = var->exec_data;
	while (data_iter)
	{
		return_type = open_red(data_iter);
		if (return_type == 1)
			break ;
		else if (return_type == 2)
			g_err = 1;
		data_iter = data_iter->forward;
	}
}

void	close_red_exec(t_mini_data *var)
{
	t_command_table	*data_iter;

	data_iter = var->exec_data;
	while (var->nodes != 0)
	{
		if (data_iter->fdout != 1)
			close(data_iter->fdout);
		if (data_iter->fdin != 0)
			close(data_iter->fdin);
		data_iter = data_iter->forward;
		var->nodes--;
	}
}

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
