/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 02:30:34 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static void	exec_loop(t_mini_data *var)
{
	t_command_table	*data_iter;
	int				return_type = 0;

	data_iter = var->exec_data;
	while (data_iter)
	{
		return_type = open_red(data_iter);
		if (return_type == 1)
			break ;
		else if (return_type == 2)
			var->err_no = 1;
		data_iter = data_iter->forward;
	}
	if (var->nodes == 1)
	{
		if (one_cmd(var->exec_data, &var->env_var) == 2)
		{
			if (!var->err_no)
				var->err_no = 127;
		}
		else
			var->err_no = 0;
	}
	else
	{
		if (multi_cmd(var->exec_data, &var->env_var) == 1)
		{
			if (!var->err_no)
				var->err_no = 127;
		}
		else
			var->err_no = 0;
	}
	while (var->nodes != 0)
	{
		if (var->exec_data->fdout != 1)
			close(var->exec_data->fdout);
		if (var->exec_data->fdin != 0)
			close(var->exec_data->fdin);
		var->exec_data = var->exec_data->forward;
		var->nodes--;
	}
	unlink_opened_files();
}

char *join_it(char *s1, char *s2, int flag)
{
	char *new_string;
	char *tmp1;
	char *tmp2;

	tmp1 = s1;
	tmp2 = s2;
	new_string = ft_strjoin(s1,s2);
	if (flag == 1)
		return (free(tmp1),new_string);
	else if (flag == 2)
		return (free(tmp2),new_string);
	else if (flag == 3)
		return (free(tmp1),free(tmp2),new_string);
	return (new_string);
}

static bool	parse_loop(t_mini_data *var, char *prompt) // norms notes
{
	char	*prompty;

	prompty = prompt;
	prompt = ft_strtrim(prompty, " ");
	free(prompty); // check on it
	if (token_catcher(prompt, var) == TRUE) // not ok 
		return (tok_free(var->tokens, 1), var->err_no = 258, 1);
	if (parser(var) == TRUE) // ok 
		return (tok_free(var->tokens, 1), var->err_no = 258, 1);
	if (expander(var) == TRUE) // not ok 
		return (tok_free(var->tokens, 1), var->err_no = 258, 1);
	if (allocate_groups(var) == TRUE) // ok
		return (cmd_free(var->exec_data, 1), tok_free(var->tokens, 1), var->err_no = 258, 1);
	if (linker(var) == TRUE) // ok
		return (cmd_free(var->exec_data, 1), var->err_no = 258, 1);
	t_command_table *test = var->exec_data;
	int i = 0;
	while(test)
	{
	    t_redirection *test2 = test->redirections;
	    while(test->cmds_array[i])
	    {
	        printf("command[%d] == %s\n",i,test->cmds_array[i]);
	        i++;
	    }
	    printf("command[%d] == %s\n",i,test->cmds_array[i]);
	    i = 0;
	    while(test2)
	    {
	        printf("type = %d | file = %s\n",test2->r_type,test2->file_name);
	        test2 = test2->next;
	    }
	    printf("file = %p\n",test2);
	    test = test->forward;
	    printf("end\n");
	}
	return (0);
}

void	signal_handler(int signal)
{
	(void)signal;
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*prompt_generator(t_mini_data *var)
{
	char *prompt;
	char *code;
	char *tmp;

	if (var->err_no == 0)
		code = GREEN;
	else
		code = RED;

	code = ft_strjoin(code,"->");
	tmp = getcwd(NULL, 0);
    prompt = ft_strjoin(CYAN "  le minishit " YELLOW, tmp);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(code , prompt);
	free(code);
	free(tmp);
	tmp = prompt;
	prompt = ft_strjoin(prompt , DEFAULT "$ ");
	free(tmp);
	return (prompt);
}

int	main(int ac, char **av, char **env)
{
	char		*prompt;
	char 		*tmp;
	t_mini_data	var;

	(void)av;
	var.env_var = NULL;
	get_env(&var.env_var, env);
	tmp = ft_itoa(ft_atoi(value_by_key(var.env_var, "SHLVL")) + 1);
	var.env_var = update_env(&var.env_var, tmp, "SHLVL");
	var.err_no = 0;
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
			tmp = prompt_generator(&var);
			prompt = readline(tmp);
			free(tmp);
			if (shell_history(&var, prompt) == TRUE)
				continue ;
			if (parse_loop(&var, prompt) == TRUE)
				continue ;
			// exec_loop(&var);
			cmd_free(var.exec_data, 1);
		}
		return (0);
	}
	return (ft_fprintf(2, "le minishell: this shell does not accept any arguments !!\n"), 127);
}

