/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:30 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/21 04:36:20 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	me_pwd(int fd, t_env *env)
{
	t_env	*tmp;
	
	tmp = env;
	if (!value_by_key(tmp, "PWD"))
	{
		tmp = env;
		tmp = update_pwd(&tmp, getcwd(NULL, 0));
	}
	ft_putstr_fd(value_by_key(tmp, "PWD"), fd);
	ft_putstr_fd("\n", fd);
}
// check for leaks 