/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:24 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 21:29:44 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	seen_bef(char *seen, char *new_val, t_env **env, int plus_flg)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(seen, tmp->key) == 0)
		{
			set_new_value(tmp, new_val, plus_flg);
			set_new_value_tow(tmp, new_val, plus_flg);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	add_key(char *arg, int plus_flg, char *value, t_env **ev)
{
	char	*key;
	t_env	*tmp;

	tmp = *ev;
	key = get_key_plus(arg);
	value = get_val(arg);
	if (!value)
	{
		if (seen_it(key, ev) != 0)
		{
			tmp = ft_lstnew_env(ft_strdup(key), value);
			ft_lstadd_back_env(ev, tmp);
		}
	}
	else
	{
		seen_bef(key, value, ev, plus_flg);
		if (seen_it(key, ev))
		{
			tmp = ft_lstnew_env(ft_strdup(key), value);
			ft_lstadd_back_env(ev, tmp);
		}
	}
	free(key);
}

int	export_item(char **arg, t_env **ev)
{
	int		i;
	int		plus_flg;
	char	*key;
	char	*value;

	i = 1;
	plus_flg = 0;
	value = NULL;
	while (arg[i])
	{
		key = get_key(arg[i]);
		if (check_valid_key(key, &plus_flg) == -1)
		{
			free(key);
			return (ft_fprintf(2, "`%s': not a valid identifier\n", arg[i]), -1);
		}
		else
		{
			add_key(arg[i], plus_flg, value, ev);
			plus_flg = 0;
		}
		i++;
	}
	return (0);
}

int	export_it(char **av, t_env **env)
{
	t_env	*tmp;
	int		ret;

	tmp = *env;
	ret = 0;
	if (tmp)
		sort_list(tmp, compare);
	if (!av[1] || !(*av[1]))
	{
		while (tmp != 0)
		{
			if (!tmp->value)
				ft_fprintf(1, "declare -x %s\n", tmp->key);
			else
				ft_fprintf(1, "declare -x %s=%c%s%c\n", tmp->key, '"', \
					tmp->value, '"');
			tmp = tmp->next;
		}
	}
	else
		ret = export_item(av, env);
	return (ret);
}
