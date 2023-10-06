/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:30 by otaraki           #+#    #+#             */
/*   Updated: 2023/10/05 04:06:23 by otaraki          ###   ########.fr       */
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
		ft_fprintf(fd, "%s\n", value_by_key(tmp, "PWD"));
	}
	else
		ft_fprintf(fd, "%s\n", str);
	free(str);
}
