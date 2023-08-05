/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/05 03:23:07 by ebennix          ###   ########.fr       */
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

int ft_iseparateur(char c);
int ft_iswhite_space(char c);
void    ft_lstdoubly(t_token **head , t_token *node);

t_token *get_tokens(char *prompt);


#endif
