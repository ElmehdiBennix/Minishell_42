/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:35 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/06 21:09:35 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_unset(char **arg, t_env **env)
{
	int	i;

	i = 0;
	while (arg[++i])
		ft_remove_node(env, arg[i], ft_strcmp);
}
