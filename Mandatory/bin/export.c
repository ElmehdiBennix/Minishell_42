/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:24 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/08 11:40:44 by otaraki          ###   ########.fr       */
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

void	export_it(char **av, t_env *env)
{
	t_env *tmp;

	tmp = env;
	(void)av;
	if (tmp)
		sort_list(tmp, compare);
	if (!av[1])
	{
		while (tmp != 0)
		{
			printf("declare -x %s=%c%s%c\n", tmp->key,'"',  tmp->value, '"');
			tmp = tmp->next;
		}
	}
	// export_item(av, env, compare);
}