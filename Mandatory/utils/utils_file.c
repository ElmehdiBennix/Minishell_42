/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:13:56 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 21:30:17 by otaraki          ###   ########.fr       */
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

int	seen_it(char *seen, t_env **env)
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

int	check_valid_key(char *key, int *plus_flg)
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
