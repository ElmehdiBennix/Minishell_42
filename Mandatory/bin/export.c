/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:24 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/02 20:21:04 by otaraki          ###   ########.fr       */
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

char	*get_key_plus(char *line)
{
	char	*key;
	int		i;

	i = 0;
	while (line[i] && (line[i] != '=' && line[i] != '+'))
		i++;
	key = malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (line[i] && (line[i] != '=' && line[i] != '+'))
	{
		key[i] = line[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	seen_bef(char *seen, char *new_val, t_env **env, int plus_flg)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(seen, tmp->key) == 0)
		{
			if ((tmp->value) && (plus_flg == 0))
				free(tmp->value);
			else if ((tmp->value) && (new_val != NULL) && (plus_flg != 0))
				tmp->value = ft_strjoin(tmp->value, new_val);
			if (new_val != NULL && (plus_flg == 0))
				tmp->value = ft_strdup(new_val);
			else if (new_val == NULL)
				tmp->value = ft_strdup("");
			return (0);
		}
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
		if (!(key[i] == '_' || key[i] == '+' || ft_isalpha(key[i])) || ((*plus_flg) > 1))
			return (-1);
		i++;
	}
	return (i);
}

void	export_item(char **arg, t_env **ev)
{
	int		i;
	int		v;
	int		plus_flg;
	char	*key;
	char	*value;
	t_env	*tmp;

	i = 1;
	v = 0;
	plus_flg = 0;
	while (arg[i])
	{
		key = get_key(arg[i]);
		v = check_valid_key(key, &plus_flg);
		free(key);
		key = NULL;
		if (v == -1)
			printf("`%s': not a valid identifier\n", arg[i]);
		else
		{
			key = get_key_plus(arg[i]);
			value = get_val(arg[i]);
			if (seen_bef(key, value, ev, plus_flg) != 0)
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
	if (!av[1])
	{
		while (tmp != 0)
		{
			if (!tmp->value)
				printf("declare -x %s=%c%c\n", tmp->key, '"', '"');
			else
				printf("declare -x %s=%c%s%c\n", tmp->key, '"', tmp->value,
						'"');
			tmp = tmp->next;
		}
	}
	else
		export_item(av, env);
}
