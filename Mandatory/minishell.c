/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:17:11 by otaraki           #+#    #+#             */
/*   Updated: 2023/07/24 00:06:09 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char *get_key(char *line)
{
    char *key;
    int i;

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
    t_env *tmp;

    tmp = NULL;
    (void)Henv;
    int     i;

    i = 0;
    while(env[i])
    {
        tmp = ft_lstnew_env(get_key(env[i]), get_val(env[i]));
        if (!tmp)
            return (0);
        ft_lstadd_back(Henv, tmp);
        i++;
    }
    return 1;
}

int main(int ac, char **av, char **env)
{
    t_env *l_env;

    (void)ac;
    (void)av;
    get_env(&l_env, env);
    while(l_env)
    {
        printf("%s=%s\n", l_env->key, l_env->value);
        l_env = l_env->next;
    }
    // get_fstr();
    (void)l_env;
}