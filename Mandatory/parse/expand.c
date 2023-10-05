/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:27:01 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 01:02:22 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	multi_key(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c < 123) || (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

int single_key(int c)
{
	if (c == '?' || c == '@'|| c == '#'|| c == '$'|| c == '-'|| c == '&' || c == '*' || c == ';' || c == '!'|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*get_value(char *content, t_mini_data *var)// algor wroking fine need work need to be done to make it understandable
{
	t_expansions exp;

	char *key;
	char *expnd_d;
	char *tmp;

	exp.new_arg = NULL;
	exp.i = 0;
	exp.j = 0;
	exp.f = 0;
	char *buffer = NULL;
	while (content[exp.i])
	{
		while (content[exp.i] && content[exp.i] == '$') // token identifier for an expand
		{
			exp.i++;
			exp.f++;
			if (content[exp.i] && single_key(content[exp.i]) == TRUE) // collect valid key to expand
			{
				exp.i++;
				exp.j++;
			}
			else
			{
				while (content[exp.i] && multi_key(content[exp.i]) == TRUE) // collect valid key
				{
					exp.i++;
					exp.j++;
				}
			}
			if (exp.j > 0)
			{
				if (exp.f - 1 > 0)
				{
					exp.new_arg = ft_calloc(exp.f, sizeof(char));
					ft_memcpy(exp.new_arg, content + exp.i - exp.j - exp.f, exp.f - 1);
				}
				key = ft_calloc(exp.j + 1, sizeof(char));
				ft_memcpy(key, content + exp.i - exp.j, exp.j);
				if (*key == '?')
				{
					tmp = ft_itoa(var->err_no);
					expnd_d = ft_strjoin(exp.new_arg, tmp);
					free(exp.new_arg);
					free(tmp);
					free(key);
				}
				else
				{
					expnd_d = ft_strjoin(exp.new_arg,value_by_key(var->env_var, key));
					free(exp.new_arg);
					free(key);
				}
				tmp = buffer;
				buffer = ft_strjoin(tmp, expnd_d);
				free(expnd_d);
				free(tmp);
				exp.f = 0;
				exp.j = 0;
				exp.new_arg = NULL;
			}
		}
		if (content[exp.i] == '\0')
			break ;
		exp.f++;
		exp.i++;
	}
	if (exp.f > 0)
	{
		exp.new_arg = ft_calloc(exp.f + 1, sizeof(char));
		ft_memcpy(exp.new_arg, content + exp.i - exp.j - exp.f, exp.f);
	}
	tmp = buffer;
	buffer = ft_strjoin(tmp, exp.new_arg);
	free(tmp);
	free(exp.new_arg);
	return (buffer);
}

bool	expander(t_mini_data *var)
{
	char c;
	char *tmp;
	t_token *arrow;

	arrow = var->tokens;
	while (arrow)
	{
		if (arrow->type >= WORD && arrow->type <= DOUBLE_QUOT)
		{
			if (arrow->type == DOUBLE_QUOT || arrow->type == SINGLE_QUOT)
			{
				c = *arrow->content;
				tmp = arrow->content;
				arrow->content = ft_strtrim(tmp, &c);
				free(tmp);
			}
			if (arrow->type == WORD || arrow->type == DOUBLE_QUOT)
			{
				tmp = arrow->content;
				if (arrow->type == WORD && ft_strncmp(arrow->content, "~", 2) == 0)
					arrow->content = ft_strdup(value_by_key(var->env_var, "HOME"));
				else if (arrow->type == WORD && ft_strncmp(arrow->content, "~/", 2) == 0)
					arrow->content = ft_strjoin(value_by_key(var->env_var, "HOME"), get_value(arrow->content + 1, var));
				else
					arrow->content = get_value(arrow->content, var);
				free(tmp);
			}
		}
		arrow = arrow->forward;
	}
	return (0);
}
