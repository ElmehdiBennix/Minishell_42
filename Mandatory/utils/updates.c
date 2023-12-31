/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:05:44 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 23:06:31 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*prompt_generator(void)
{
	char	*prompt;
	char	*code;

	if (g_err == 0)
		code = GREEN;
	else
		code = RED;
	prompt = join_it("->" YELLOW "  le minishit " CYAN, getcwd(NULL, 0),2);
	prompt = join_it(code, prompt, 2);
	prompt = join_it(prompt, DEFAULT "$ ",1);
	return (prompt);
}

t_env	*update_env(t_env **env, char *value, char *key)
{
	t_env	*tmp;
	int		fod;

	tmp = *env;
	fod = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			fod = 1;
			if (tmp->value)
				free(tmp->value);
			if (value != NULL)
				tmp->value = ft_strdup(value);
			tmp = *env;
			return (tmp);
		}
		tmp = tmp->next;
	}
	tmp = *env;
	if (!fod)
		ft_lstadd_back_env(&tmp, ft_lstnew_env(ft_strdup(key),
				ft_strdup(value)));
	return (tmp);
}

void	unlink_opened_files(void)
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
		s = NULL;
		i++;
		str = ft_itoa(i);
		s = ft_strjoin("/tmp/here_doc", str);
		free(str);
	}
	free(s);
}
