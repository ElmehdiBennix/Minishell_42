/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:24 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/15 17:05:28 by marvin           ###   ########.fr       */
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

int	check_valid_key(char *key, t_env *env)
{
	int i;
	t_env *tmp;

	i  = 0;
	tmp = env;
	tmp->key = NULL;
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
		if(!ft_strcmp(seen, tmp->key))
		{
			if (tmp->value != NULL && tmp->value[0] != '\0')
				free(tmp->value);
			if(new_val != NULL)
				tmp->value = ft_strdup(new_val);
			return 0;
		}
		tmp = tmp->next;
	}
	return (1);
}
void	export_item(char **arg, t_env *ev)
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
		v = check_valid_key(get_key(arg[i]), ev);
		if (v == -1)
			printf("`%s': not a valid identifier\n", arg[i]);
		else
		{
			// check value of the key if null or \0----------------------------------------------------------------
			key = get_key(arg[i]);
			value = get_val(arg[i]);
			if (seen_bef(key, value,  ev) != 0)
			{
				tmp = ft_lstnew_env(key, value);
				ft_lstadd_back_env(&ev, tmp);
			}
		}
		i++;
	}
}

void	export_it(char **av, t_env **env)
{
	t_env *tmp;

	tmp = *env;
	(void)av;
	if (tmp)
		sort_list(tmp, compare);
	if (!av[1])// av[0] = "export" av[1] = NULL .. av[n] == NULL 
	{
		while (tmp != 0)
		{
			if (!tmp->value)
				printf("declare -x %s\n", tmp->key);
			else
				printf("declare -x %s=%c%s%c\n", tmp->key, '"',  tmp->value, '"');
			tmp = tmp->next;
		}
	}
	else
	{
		export_item(av, *env);
		// export_item(av, *env);
		
	}
}
// i sill need to handel the rest of the cases to not crash