/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:53:30 by otaraki           #+#    #+#             */
/*   Updated: 2023/08/26 19:45:56 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	me_pwd(char **av, t_env **env)
{
	t_env	*tmp;
	
	(void)av;
	tmp = *env;
	if (!value_by_key(tmp, "PWD"))
	{
		tmp = *env;
		tmp = update_pwd(&tmp, getcwd(NULL, 0));
	}
	printf("%s\n", value_by_key(tmp, "PWD"));
}
// check for leaks 