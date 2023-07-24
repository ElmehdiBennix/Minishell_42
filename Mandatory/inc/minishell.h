/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/07/24 01:40:11 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include "../../lib/inc/utils.h"


typedef struct s_token
{
    int             flag_s;
    char            *content;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;


typedef struct s_lex
{
	char            *str;
	int             i;
    t_token         *token;
	struct s_lex	*next;
	struct s_lex	*prev;
}	t_lex;

typedef struct s_mini_data
{
    int     err_no;
    char    **env_var;
	char	**paths;
    char    *PWD;
    char    *OLDPWD;

}   t_mini_data;


void tokeni(char *f_line);

#endif
