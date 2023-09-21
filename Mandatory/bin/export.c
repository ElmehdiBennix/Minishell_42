/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:24 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/19 18:52:14 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int compare(char *a, char *b)
{
	int cmpa = ft_strcmp(a, b);// chekout your strcmp function
	if (cmpa > 0)
		return 0;
	else
		return -1;
}

int	check_valid_key(char *key)
{
	int i;

	i  = 0;
	while(key[i])
	{
		if (!(key[i] == '_' || key[i] == '+' 
			|| ft_isalpha(key[i])))
			return (-1);
		i++;
	}
	return (i);
}

int	seen_bef(char *seen, char *new_val, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while(tmp)
	{
		if(ft_strcmp(seen, tmp->key) == 0)
		{
			if ((tmp->value != NULL))
				free(tmp->value);
			if(new_val != NULL)
				tmp->value = ft_strdup(new_val);
			else if (new_val == NULL)
				tmp->value = ft_strdup("");
			return 0;
		}
		tmp = tmp->next;
	}
	return (1);
}
void	export_item(char **arg, t_env **ev)
{
	int 	i;
	int 	v;
	char 	*key;
	char 	*value;
	t_env 	*tmp;
	
	i = 1;
	v = 0;
	while(arg[i])
	{
		v = check_valid_key(get_key(arg[i]));
		if (v == -1)
			printf("`%s': not a valid identifier\n", arg[i]);
		else
		{
			key = get_key(arg[i]);
			value = get_val(arg[i]);
			if (seen_bef(key, value,  *ev) != 0)
			{
				tmp = ft_lstnew_env(key, value);
				ft_lstadd_back_env(ev, tmp);
			}
		}
		i++;
	}
}

void	export_it(char **av, t_env **env)
{
	t_env *tmp;

	tmp = *env;
	if (tmp)
		sort_list(tmp, compare);
	if (!av[1])// av[0] = "export" av[1] = NULL .. av[n] == NULL 
	{
		while (tmp != 0)
		{
			if (!tmp->value)
				printf("declare -x %s=%c%c\n", tmp->key, '"', '"');
			else
				printf("declare -x %s=%c%s%c\n", tmp->key, '"',  tmp->value, '"');
			tmp = tmp->next;
		}
	}
	else
		export_item(av, env);

}
// i sill need to handel the rest of the cases to not crash