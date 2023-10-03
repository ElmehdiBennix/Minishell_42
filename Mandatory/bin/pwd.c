/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:30 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/03 20:21:55 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	me_pwd(int fd, t_env **env)
{
	t_env	*tmp;
	char	*str;

	tmp = *env;
	str = getcwd(NULL, 0);
	if (!str)
	{
		tmp = *env;
		ft_putstr_fd(value_by_key(tmp, "PWD"), fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
	}
	free(str);
}
