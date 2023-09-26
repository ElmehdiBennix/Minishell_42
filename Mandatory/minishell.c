/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/26 09:07:48 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char *get_key(char *line)
{
    char *key;
    int i;

	i = 0;
    while(line[i] && line[i] != '=')
        i++;
    key = malloc(sizeof(char) * i + 1);
    if (!key)
        return (NULL);
    i = 0;
    while(line[i] && line[i] != '=')
    {
        key[i] = line[i];
        i++;
    }
    key[i] = '\0';
    return (key);
}

char *get_val(char *line)
{
    char *val;
    int i;
    int j;

    i = 0;
    while(line[i] && line[i] != '=')
        i++;
    if (!line[i] || !line[i + 1])
        return (NULL);
    j = i + 1;
    while(line[j])
        j++;
    val = malloc(sizeof(char) * (j - i + 1));
    j = i + 1;
    i = 0;
    while(line[j])
        val[i++] = line[j++];
    val[i] = '\0';
    return (val);
}

int get_env(t_env **Henv, char **env)
{
    t_env 	*tmp;
    int     i;

    i = 0;
    while(env[i])
    {
        tmp = ft_lstnew_env(get_key(env[i]), get_val(env[i]));
		if (!Henv)
			Henv = &tmp;
        else
			ft_lstadd_back_env(Henv, tmp);
        i++;
    }
    return 1;
}

static void	exec_loop(t_mini_data *var)
{
    t_command_table *data_iter = var->exec_data;

	while (data_iter)
	{
		open_red(data_iter);
		data_iter = data_iter->forward;
	}
	if (var->nodes == 1)
	{
		if (one_cmd(var->exec_data, &var->env_var) == 2)
		{
			var->err_no = 2;
			return ;
		}
	}
	else
		multi_cmd(var->exec_data, &var->env_var);
	while(var->nodes != 0)
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

static bool	parse_loop(t_mini_data *var, char *prompt)
{
    char *prompty = prompt;

	prompt = ft_strtrim(prompty, " ");
    free(prompty);
    if (!prompt)
        return (var->err_no = 3 ,1);
	if (token_catcher(prompt ,var) == TRUE)
        return (tok_free(var->tokens,1),var->err_no = 4 ,1);
	if (parser(var) == TRUE)
        return(tok_free(var->tokens,1),var->err_no = 5 ,1);
    if (expander(var) == TRUE) // leaks left and $?
        return(tok_free(var->tokens,1),var->err_no = 6 ,1);
    if (allocate_groups(var) == TRUE)
        return(cmd_free(var->exec_data,1),tok_free(var->tokens,1),var->err_no = 7 ,1);
	if (linker(var) == TRUE) // leaks left
        return(cmd_free(var->exec_data,1),tok_free(var->tokens,1),var->err_no = 8 ,1);
    tok_free(var->tokens,1);
    return(0);
}

void	unlink_opened_files()
{
		int		i;
		char	*str; 
		char	*s;

		i = 0;
		str = ft_itoa(i);
		s = ft_strjoin("/tmp/here_doc", str);
		free(str);
		while (access(s, F_OK) == 0)
		{
			str = NULL;
			unlink(s);
			free(s);
			i++;
			str = ft_itoa(i);
			s = ft_strjoin("/tmp/here_doc", str);
			free(str);
		}
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

int	main(int ac, char **av, char **env)
{
	char		*prompt;
	t_mini_data	var;

	(void)av;
	var.err_no = 0;
	var.env_var = NULL;
	get_env(&var.env_var, env);
	if (ac == 1)
	{
		while (1)
		{
            var.tokens = NULL;
            var.exec_data = NULL;
			// prompt = prompt_generator(var);
            prompt = NULL;
            signal(SIGQUIT, SIG_IGN);
            signal(SIGINT, signal_handler);
			prompt = readline(GREEN "-> le minishit" DEFAULT "$ "); // should display corrent dir and exit msgs zith colors sigf when cntr+ c or sm protect read line and make signales work
            if (shell_history(&var, prompt) == TRUE)
				continue;
			if (parse_loop(&var, prompt) == TRUE)
                continue;
			exec_loop(&var);
            cmd_free(var.exec_data,1);
		}
		return (0);
	}
	return (ft_fprintf(2,"le minishell: this shell does not accept any arguments !!\n"),127);
}

    // t_command_table *test = var->exec_data;
    // int i = 0;
    // while(test)
    // {
    //     t_redirection *test2 = test->redirections;
    //     while(test->cmds_array[i])
    //     {
    //         printf("command[%d] == %s\n",i,test->cmds_array[i]);
    //         i++;
    //     }
	//     printf("command[%d] == %s\n",i,test->cmds_array[i]);
    //     i = 0;
    //     while(test2)
    //     {
    //         printf("type = %d | file = %s\n",test2->r_type,test2->file_name);
    //         test2 = test2->next;
    //     }
	// 	printf("file = %p\n",test2);
    //     test = test->forward;
    //     printf("end\n");
    // }