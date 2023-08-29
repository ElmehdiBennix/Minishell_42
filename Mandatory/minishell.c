/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/30 00:02:48 by ebennix          ###   ########.fr       */
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
        if (!tmp)
            return (0);
        ft_lstadd_back_env(Henv, tmp);
        i++;
    }
    return 1;
}



// static void	exec_loop(t_mini_data *var) // void for now might change it in the future
// {

// }

static void	parse_loop(t_mini_data *var, char *prompt) // void for now might change it in the future
{
	prompt = ft_strtrim(prompt, " ");
	var->tokens = get_tokens(prompt);
	free(prompt);
	tokenizer(var->tokens);
	expand(var->tokens,var);
	
	// t_token *arrow = var->tokens;
	// while(arrow)
	// {
	// 	printf("%s\n",arrow->content);
	// 	arrow = arrow->forward;
	// }
	// expand(var->tokens);
	
}

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
			// prompt = prompt_generator(&var);
			// signals --
			prompt = readline(GREEN "-> le minishit" DEFAULT "$ "); // should display corrent dir and exit msgs zith colors sigf when cntr+ c or sm protect read line and make signales work
			if (shell_history(&var, prompt) == 1) // dosent store tabs empty line or empty spaces stinn needs fa function
				continue ;
			parse_loop(&var, prompt);
			// exec_loop();
		}
		return (0);
	}
	return (ft_fprintf(2,"le minishell: this shell does not accept any arguments !!\n"),127);
}