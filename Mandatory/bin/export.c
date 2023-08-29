/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:24 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/29 23:58:09 by ebennix          ###   ########.fr       */
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
			|| isalpha(key[i])))
			return -1;
		i++;
	}
	return i;
}

void	export_item(char **arg, t_env *ev)
{
	int 	i;
	int 	v;
	char 	*key;
	i = 1;
	v = 0;
	while(arg[i])
	{
		v = check_valid_key(get_key(arg[i]));
		if (v == -1)
			printf("`%s': not a valid identifier\n", arg[i]);
		// else
		// {
			
		// }
		
	}
}

void	export_it(char **av, t_env *env)
{
	t_env *tmp;

	tmp = env;
	(void)av;
	if (tmp)
		sort_list(tmp, compare);
	if (!av[1])// export NULL 
	{
		while (tmp != 0)
		{
			printf("declare -x %s=%c%s%c\n", tmp->key,'"',  tmp->value, '"');
			tmp = tmp->next;
		}
	}
	// else
	// 	export_item(av, env);
}