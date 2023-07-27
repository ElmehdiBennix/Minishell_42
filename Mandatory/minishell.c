/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:39:52 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/27 05:47:58 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	**get_path(char **env)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**path_spl;

	i = 0;
	path = NULL;
	while (env[i] && path == NULL)
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	if (path == NULL)
		return (NULL);
	path_spl = ft_split(path + 5, ':');
	i = 0;
	while (path_spl[i])
	{
		tmp = ft_strjoin(path_spl[i], "/");
		// free(path_spl[i]);
		path_spl[i] = tmp;
		i++;
	}
	return (path_spl);
}
char *get_pwds(char **env , char *key ,size_t len)
{
	int		i;
	char	*pwd;
	char	*pwd_dup;

	i = 0;
	pwd = NULL;
	while (env[i] && pwd == NULL)
	{
		pwd = ft_strnstr(env[i], key, len);
		i++;
	}
	if (pwd == NULL)
		return (NULL);
	pwd_dup = ft_strdup(pwd + len);
	return (pwd_dup);
}

typedef enum
{
	PIPE = 1,
	SINGLE_QUOTE = 2,
	DOUBLE_QUOTE = 3,
	GREATE = 4,
	LESS = 5,
	GREATE_GREATE = 6,
	LESS_LESS = 7,

}	tokens;

bool	basic_parse_check(char *prompt)
{
	int i;
	bool status;

	status = false;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == 34 || prompt[i] == 39)
		{
			char quot = prompt[i];
			status = true;
			i++;
			while (prompt[i] && prompt[i] != quot)
				i++;
			if (prompt[i] == quot)
				status = false;
		}
		i++;
	}
	return (status);
}

void shell_loop(t_mini_data *var) // void for now might change it in the future
{
    char *prompt;

	(void)var;
    while (1)
    {
        prompt = readline("le minishit : "); // should display corrent dir and exit msgs zith colors
        // ft_fprintf(1,"%s\n",prompt);
		prompt = ft_strtrim(prompt," ");
        ft_fprintf(1,"%s\n",prompt);
		printf("*****************************\n");
		if (basic_parse_check(prompt) == true)
			exit_msg(1,"error",RED,41);
        tokenizer(prompt);
        // parsing(prompt);
    }
}

char **get_env(char **env) // add it as a linked list with key value makes job easier in future
{
	int i;
	char **env_ptr;

	i = 0;
    while(env[i])
		i++;
	env_ptr = ft_calloc(i + 1,sizeof(char *));
	i = 0;
    while(env[i])
    {
        env_ptr[i] = ft_strdup(env[i]);
        i++;
    }
    return(env_ptr);
}

int main(int ac, char **av , char **env)
{
    // extern char **environ;
    t_mini_data var;
	(void)ac;
	(void)av;

    char **p = get_env(env);
	while(*p)
	{
		printf("%s\n",*p);
		p++;
	}
	printf("%s\n",*p);
	printf("==============================================================================");
    printf("%s\n",get_pwds(env,"PWD=",4));
	printf("==============================================================================");
    printf("%s\n",get_pwds(env,"OLDPWD=",7));
	printf("==============================================================================");
    char **x = get_path(env);
	while(*x)
	{
		printf("%s\n",*x);
		x++;
	}
	printf("%s\n",*x);
	printf("==============================================================================\n");

    shell_loop(&var);
}

// leaks and misisng alot of protection in case of a fail