/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/05 04:58:28 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include "../../lib/inc/utils.h"

typedef enum s_type
{
    WORD = 1,
	PIPE = 2,
	SINGLE_QUOT = 3,
	DOUBLE_QUOT = 4,
	GREAT = 5,
	LESS = 6,
	GREAT_GREAT = 7,
	LESS_LESS = 8,
    PIPE_RED = 9,

}	t_type;

typedef struct s_token
{
    int             id;
    char            *content;
    bool            space_after;
    t_type          type;
    struct s_token  *forward;
    struct s_token  *backward;
} t_token;

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
// t_lex *tokenizer(t_token *tokens);


#endif
