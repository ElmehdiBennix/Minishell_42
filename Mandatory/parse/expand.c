/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:27:01 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/06 19:51:33 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	expand_variable(t_expansions *exp, char *content, t_mini_data *var)
{
	char	*key;
	char	*expnd_d;

	key = NULL;
	expnd_d = NULL;
	if (exp->f - 1 > 0)
	{
		exp->new_arg = ft_calloc(exp->f, sizeof(char));
		ft_memcpy(exp->new_arg, content + exp->i - exp->j - exp->f, exp->f - 1);
	}
	key = ft_calloc(exp->j + 1, sizeof(char));
	ft_memcpy(key, content + exp->i - exp->j, exp->j);
	if (key && *key == '?')
		expnd_d = join_it(exp->new_arg, ft_itoa(g_err), 3);
	else
		expnd_d = join_it(exp->new_arg, value_by_key(var->env_var, key), 1);
	free(key);
	exp->buffer = join_it(exp->buffer, expnd_d, 3);
	exp->new_arg = NULL;
	exp->f = 0;
	exp->j = 0;
}

static void	collect_variable(t_expansions *exp, char *content, t_mini_data *var)
{
	while (content[exp->i] && content[exp->i] == '$')
	{
		exp->i++;
		exp->f++;
		if (content[exp->i] && single_key(content[exp->i]) == TRUE)
		{
			exp->i++;
			exp->j++;
		}
		else
		{
			while (content[exp->i] && multi_key(content[exp->i]) == TRUE)
			{
				exp->i++;
				exp->j++;
			}
		}
		if (exp->j > 0)
			expand_variable(&(*exp), content, var);
	}
}

char	*get_value(char *content, t_mini_data *var)
{
	t_expansions	exp;

	ft_bzero(&exp, sizeof(exp));
	while (content[exp.i])
	{
		collect_variable(&exp, content, var);
		if (content[exp.i] == '\0')
			break ;
		exp.i++;
		exp.f++;
	}
	if (exp.f > 0)
	{
		exp.new_arg = ft_calloc(exp.f + 1, sizeof(char));
		ft_memcpy(exp.new_arg, content + exp.i - exp.j - exp.f, exp.f);
	}
	exp.buffer = join_it(exp.buffer, exp.new_arg, 3);
	return (exp.buffer);
}

static void	exp_cases(t_mini_data *var, t_token *arrow)
{
	char	*tmp;

	tmp = arrow->content;
	if (arrow->type == WORD && ft_strncmp(arrow->content, "~", 2) == 0)
		arrow->content = ft_strdup(value_by_key(var->env_var, "HOME"));
	else if (arrow->type == WORD && ft_strncmp(arrow->content, "~/", 2) == 0)
		arrow->content = ft_strjoin(value_by_key(var->env_var, "HOME"),
				get_value(arrow->content + 1, var));
	else
		arrow->content = get_value(arrow->content, var);
	free(tmp);
}

bool	expander(t_mini_data *var)
{
	char	c;
	char	*tmp;
	t_token	*arrow;

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
				exp_cases(var, arrow);
		}
		arrow = arrow->forward;
	}
	return (0);
}
