/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/21 06:45:10 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"
// leaks and misisng alot of protection in case of a fail

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

static void	exec_loop(t_mini_data *var) // void for now might change it in the future
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

static void	parse_loop(t_mini_data *var, char *prompt) // void for now might change it in the future
{
	prompt = ft_strtrim(prompt, " ");
	var->tokens = get_tokens(prompt);
	free(prompt);
    // printf("nodes = %d \n",var->nodes);
	tokenizer(var);
	expand(var);
    // printf("nodes 2 = %d \n",var->nodes);
    // t_token *tok = var->tokens;
    // while(tok)
    // {
    //     printf("token == %s\n",tok->content);
    //     tok = tok->forward;
    // }
	group_args(var);
    linker(var);
    // t_command_table *cmds = var->exec_data;
    // int i ;
    // while(cmds)
    // {
    //     i = 0;
    //     while(cmds->cmds_array[i])
    //     {
    //         printf("args == %s\n",cmds->cmds_array[i]);
    //         i++;
    //     }
    //     printf("args == %s\n",cmds->cmds_array[i]);
    //     while(cmds->redir)
    //     {
    //         printf("redirection file == %s , type == %d\n",cmds->redir->file_name,cmds->redir->redirection);
    //         cmds->redir = cmds->redir->next;
    //     }
    //     cmds = cmds->forward;
    // }
}

// int main(int ac, char **av, char **env)
// {
//     t_env *l_env;
// 	char *content;
// 	char **cmds;
// 	t_token *token;
	
//     (void)ac;
//     (void)av;

// 	l_env = NULL;
//     get_env(&l_env, env);
// 	while (1)
// 	{
// 		content = readline("-->MIMI :");
// 		if (content == NULL)
// 			break  ;
// 		cmds = ft_split(content, '|');
// 		if (cmds == NULL)
// 			continue ;
// 		token = fake_struct(cmds);
// 		if (!token)
// 			continue ;
// 		free_array(cmds);
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
// 		free_struct_data(token);
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
			// prompt = prompt_generator(var);           
            // signals --
            prompt = NULL;
			prompt = readline(GREEN "-> le minishit" DEFAULT "$ "); // should display corrent dir and exit msgs zith colors sigf when cntr+ c or sm protect read line and make signales work
            if (shell_history(&var, prompt) == 1) // dosent store tabs empty line or empty spaces stinn needs fa function
				continue;
			parse_loop(&var, prompt);
            // free(prompt);
            // free(var.tokens);
			exec_loop(&var);
            // free(var.exec_data);
		}
		return (0);
	}
	return (ft_fprintf(2,"le minishell: this shell does not accept any arguments !!\n"),127);
}
