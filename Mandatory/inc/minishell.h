/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/04 23:56:53 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include "../../lib/inc/utils.h"


typedef struct s_token
{
    char            *content;
    bool            space_after;
    struct s_token  *forward;
    struct s_token  *backward;
} t_token;


typedef struct s_lex
{
	int             id;
	char            *key_word;
    t_token         *token;
	struct s_lex	*forward;
	struct s_lex	*backward;
}	t_lex;

typedef struct s_mini_data
{
    int     err_no;
    char    **env_var;
	char	**paths;
    char    *PWD;
    char    *OLDPWD;

}   t_mini_data;


t_token *tokenizer(char *prompt);

#endif
