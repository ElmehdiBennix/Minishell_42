/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:26:24 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/23 03:45:19 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int change_dir(char *path)
{
    // const   char *absu = "/Users/ebennix"; //this is an example
    // appand it the pwd command
    // absolute path should go directly to it
    // if its cd only it should go to last history

    if (chdir(path) == 0) {
        return (0);
    } else {
        perror("cd");
}