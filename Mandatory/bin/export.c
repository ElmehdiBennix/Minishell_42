/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:24 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 01:14:21 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	compare(char *a, char *b)
{
	int	cmpa;

	cmpa = ft_strcmp(a, b);
	if (cmpa > 0)
		return (0);
	else
		return (-1);
}

static int	seen_it(char *seen, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(seen, tmp->key) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

static int	check_valid_key(char *key, int *plus_flg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]))
		return (-1);
	while (key[i])
	{
		if (key[i] == '+')
			(*plus_flg)++;
		if (!(key[i] == '_' || key[i] == '+' || ft_isalnum(key[i]))
			|| ((*plus_flg) > 1))
			return (-1);
		i++;
	}
	if (key)
		free(key);
	return (i);
}
void	set_new_value(t_env *tmp, char *new_val, int plus_flg)
{
	char	*str;

	str = NULL;
	if (!(tmp->value) && (plus_flg == 0) && new_val)
	{
		str = new_val;
		tmp->value = ft_strdup(new_val);
		free(str);
	}
	else if ((tmp->value) && (plus_flg == 0) && new_val)
	{
		free(tmp->value);
		str = new_val;
		tmp->value = ft_strdup(new_val);
		free(str);
	}
}

void	set_new_value_tow(t_env *tmp, char *new_val, int plus_flg)
{
	char	*str;
	char	*ftr;

	str = NULL;
	ftr = NULL;
	if (!(tmp->value) && !(new_val) && (plus_flg == 0))
		tmp->value = ft_strdup("");
	else if ((tmp->value) && (plus_flg != 0) && new_val)
	{
		str = tmp->value;
		ftr = new_val;
		tmp->value = ft_strjoin(tmp->value, new_val);
		free(str);
		free(ftr);
	}
}

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
			return(ft_fprintf(2, "`%s': not a valid identifier\n", arg[i]), -1);
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
				ft_fprintf(1, "declare -x %s=%c%s%c\n", tmp->key, '"', tmp->value,
						'"');
			tmp = tmp->next;
		}
	}
	else
		ret = export_item(av, env);
	return (ret);
}
