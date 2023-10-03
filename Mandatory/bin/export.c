/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:24 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/03 19:36:44 by otaraki          ###   ########.fr       */
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

int	seen_bef(char *seen, char *new_val, t_env **env, int plus_flg)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(seen, tmp->key) == 0)
		{
			if (!(tmp->value) && (plus_flg == 0) && new_val)
				tmp->value = ft_strdup(new_val);
			else if ((tmp->value) && (plus_flg == 0) && new_val)
			{
				free(tmp->value);
				tmp->value = ft_strdup(new_val);
			}
			else if(!(tmp->value) && !(new_val) && (plus_flg == 0))
				tmp->value = ft_strdup("");
			else if ((tmp->value) && (plus_flg != 0))
				tmp->value = ft_strjoin(tmp->value, new_val);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	seen_it(char *seen, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(seen, tmp->key))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	check_valid_key(char *key, int *plus_flg)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '+')
			(*plus_flg)++;
		if (!(key[i] == '_' || key[i] == '+' || ft_isalpha(key[i])) \
			|| ((*plus_flg) > 1))
			return (-1);
		i++;
	}
	return (i);
}
void	export_item(char **arg, t_env **ev)
{
	int		i;
	int		plus_flg;
	char	*key;
	char	*value;
	int		assigned;
	t_env	*tmp;

	i = 1;
	plus_flg = 0;
	assigned = 0;
	while (arg[i])
	{
		key = get_key(arg[i]);
		if (check_valid_key(key, &plus_flg) == -1)
			printf("`%s': not a valid identifier\n", arg[i]);
		else
		{
			free(key);
			key = NULL;
			key = get_key_plus(arg[i]);
			value = get_val(arg[i]);
			if (seen_it(key, ev) != 0 && !value)
			{
				tmp = ft_lstnew_env(key, value);
				ft_lstadd_back_env(ev, tmp);
			}
			else if (seen_bef(key, value, ev, plus_flg) != 0 && value)
			{
				tmp = ft_lstnew_env(key, value);
				ft_lstadd_back_env(ev, tmp);
			}
			plus_flg = 0;
		}
		i++;
	}
}

void	export_it(char **av, t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp)
		sort_list(tmp, compare);
	if (!av[1] || !(*av[1]))
	{
		while (tmp != 0)
		{
			if (!tmp->value)
				printf("declare -x %s\n", tmp->key);
			else
				printf("declare -x %s=%c%s%c\n", tmp->key, '"', tmp->value,
					'"');
			tmp = tmp->next;
		}
	}
	else
		export_item(av, env);
}
