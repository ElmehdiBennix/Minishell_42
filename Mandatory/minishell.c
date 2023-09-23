/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/23 22:51:51 by ebennix          ###   ########.fr       */
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

// void exceute_it(t_token **data, t_env **env)
static void	exec_loop(t_mini_data *var)
{
    t_command_table *data_iter = var->exec_data;

	// while (data_iter)
	// {
	// 	open_red(data_iter);
	// 	data_iter = data_iter->forward;
	// }
	if (var->nodes == 1)
		one_cmd(var->exec_data, var->env_var);
	else
		multi_cmd(var->exec_data, var->env_var);
}

static bool	parse_loop(t_mini_data *var, char *prompt)
{
    // norm left
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
        i = 0;
        while(test2)
        {
            printf("type = %d | file = %s\n",test2->r_type,test2->file_name);
            test2 = test2->next;
        }
        test = test->forward;
        printf("end\n");
    }

    return(0);
}

// int main(int ac, char **av, char **env)
// {
// 	{
// 		exceute_it(&token, &l_env);
// 		int i = 0;
// 		char *s = ft_strjoin("/tmp/here_doc", ft_itoa(i));
// 		while (access(s, F_OK) == 0)
// 		{
// 			unlink(s);
// 			free(s);
// 			i++;
// 			s = ft_strjoin("/tmp/here_doc", ft_itoa(i));//leaks
// 		}
// 	}
// }

int	main(int ac, char **av, char **env)
{
	char		*prompt;
	t_mini_data	var;

	(void)av;
	var.err_no = 0;
	var.env_var = NULL;
	get_env(&var.env_var,env);
	if (ac == 1)
	{
		while (1)
		{
            var.tokens = NULL;
            var.exec_data = NULL;
			// prompt = prompt_generator(var);
            // signals --
            prompt = NULL;
			prompt = readline(GREEN "-> le minishit" DEFAULT "$ "); // should display corrent dir and exit msgs zith colors sigf when cntr+ c or sm protect read line and make signales work
            if (shell_history(&var, prompt) == TRUE)
				continue;
			if (parse_loop(&var, prompt) == TRUE)
                continue;
			// exec_loop(&var);
            cmd_free(var.exec_data,1);
		}
		return (0);
	}
	return (ft_fprintf(2,"le minishell: this shell does not accept any arguments !!\n"),127);
}
