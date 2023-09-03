/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:30 by otaraki           #+#    #+#             */
/*   Updated: 2023/09/03 21:46:31 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	me_pwd(int fd, char **av, t_env **env)
{
	t_env	*tmp;
	
	(void)av;
	tmp = *env;
	if (!value_by_key(tmp, "PWD"))
	{
		tmp = *env;
		tmp = update_pwd(&tmp, getcwd(NULL, 0));
	}
	ft_putstr_fd(value_by_key(tmp, "PWD"), fd);
	ft_putstr_fd("\n", fd);
}
// check for leaks 