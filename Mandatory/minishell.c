/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:17:11 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/03 23:38:22 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char *get_key(char *line)
{
    char *key;
    int i;

	i = 0;
    while(line[i] && line[i] != '=') // think about this case a+=toto (append the value to env value)
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
    while(line[i] && line[i] != '=')// availi
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

int main(int ac, char **av, char **env)
{
    t_env *l_env;
	char *content;
	char **cmds;
	t_token *token;
	
    (void)ac;
    (void)av;

	l_env = NULL;
    get_env(&l_env, env);
	while (1)
	{
		content = readline("MIMI :");
		// printf("------------------------------\n");
		// cmds = ft_split(content, ' ');
		cmds = ft_split(content, '|');
		// ft_bultin(cmds, &l_env);
		token = fake_struct(cmds);
		token->fdin = 0;
		token->fdout = 1;
		// printf("%d\n", GREAT);
		exceute_it(&token, &l_env);
		// I only excute one cmd case still working 
			// on multiple cmds && handeling pipes fds
	}
}
		// printf("%d\n", ft_bultin(cmds, l_env));