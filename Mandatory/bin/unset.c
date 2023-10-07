/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:35 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/07 01:26:51 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(char **arg, t_env **env)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (!ft_isalpha(arg[i][0]) && (arg[i][0] != '_'))
		{
			ft_fprintf(2, "unset: `%s': not a valid identifier\n", arg[i]);
			g_err = 1;
		}
		else
			ft_remove_node(env, arg[i], ft_strcmp);
	}
	if (g_err == 1)
		return (-1);
	return (0);
}
