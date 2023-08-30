/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:05:55 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/30 21:45:57 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*check_redis(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '>')
			return (&str[i]);
		else if (str[i] == '<')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

int set_outfile(char *str)
{
	int outfile = open(str, O_CREAT, 0666);
	return outfile;
}
int set_infile(char *str)
{
	int infile = open(str, O_CREAT, 0666);
	return infile;
}

void	one_cmd(t_token **data_cmd, t_env **env)
{
	t_token *cmd;
	char	*str;
	int 	i;

	(void)env;
	cmd = *data_cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->content[i])// ls > la | haha < infile
		{
			str = ft_strdup(check_redis(cmd->content[i]));
			if (str[0] == '>')
				dup2(set_outfile(str), 1);
			else if (str[0] == '<')
				dup2(set_infile(str), 0);
			i++;
		}
	}
		
}

void	pipe_first(t_token **data_arg, t_env **env)	
{
	t_token *iter;
	int		numb_pipes;
	// int		**fd;

	iter = *data_arg;
	numb_pipes = -1;
	while (iter)
	{
		numb_pipes++;
		iter = iter->forward;// I am gonna check if theres a | 
	}
	if (numb_pipes == 0)
		one_cmd(data_arg, env);
}

void	exceute_it(t_token **data, t_env **env)
{
	pipe_first(data, env);
}